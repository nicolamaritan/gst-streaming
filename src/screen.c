#include "../include/screen.h"

void init_screen_sender_data(Screen_Sender_Data* data, gchar* target_ip)
{
    // gst-launch-1.0 ximagesrc ! video/x-raw ! videoconvert ! x264enc ! h264parse ! rtph264pay ! udpsink host=127.0.0.1 port=5000
    
    // empty pipeline
    data->pipeline = gst_pipeline_new("sender-pipeline");

    // Source
    data->source = gst_element_factory_make("ximagesrc", "source");
        
    // Caps filter and params
    data->caps_filter = gst_element_factory_make ("capsfilter", "capsfilter");
    g_object_set(data->caps_filter, "caps", gst_caps_from_string("video/x-raw"), NULL);
    
    // Convert
    data->convert = gst_element_factory_make("videoconvert", "convert");
    
    // Encoder and params
    data->encoder = gst_element_factory_make("x264enc", "encoder");
    gint zerolatency = 0x00000004;  // Ref: https://gstreamer.freedesktop.org/documentation/x264/index.html?gi-language=c#GstX264EncTune
    gint bitrate = 1000;
    gint threads = 4;
    g_object_set(data->encoder, "tune", zerolatency, NULL);
    g_object_set(data->encoder, "bitrate", bitrate, NULL);
    g_object_set(data->encoder, "byte-stream", TRUE, NULL);
    g_object_set(data->encoder, "threads", threads, NULL);

    // Parser
    data->parser = gst_element_factory_make("h264parse", "parser");
    
    // Pay
    data->pay = gst_element_factory_make("rtph264pay", "pay");

    // Sink and params
    data->sink = gst_element_factory_make("udpsink", "sink");
    //g_object_set(data->sink, "host", "192.168.1.4", NULL);
    g_object_set(data->sink, "host", "127.0.0.1", NULL);
    g_object_set(data->sink, "port", 5000, NULL);

    
}

void launch_screen_sender(gchar* target_ip)
{
    Screen_Sender_Data sender_data;
    GstBus* bus;
    GstStateChangeReturn ret;
    GstMessage* msg;
    gboolean terminate = FALSE;

    init_screen_sender_data(&sender_data, target_ip);
    
    // Adding binaries
    gst_bin_add_many(GST_BIN(sender_data.pipeline),
                     sender_data.source,
                     sender_data.caps_filter,
                     sender_data.convert,
                     sender_data.encoder,
                     sender_data.parser,
                     sender_data.pay,
                     sender_data.sink,
                     NULL);

    // Linking elements
    if (!gst_element_link_many (sender_data.source,
                           sender_data.caps_filter,
                           sender_data.convert,
                           sender_data.encoder,
                           sender_data.parser,
                           sender_data.pay,
                           sender_data.sink,
                           NULL))
    {
        g_printerr ("Elements could not be linked.\n");
        gst_object_unref (sender_data.pipeline);
        return;
    }

    

    ret = gst_element_set_state(sender_data.pipeline, GST_STATE_PLAYING);

    if (ret == GST_STATE_CHANGE_FAILURE) 
    {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (sender_data.pipeline);
        return;
    } 

    bus = gst_element_get_bus(sender_data.pipeline);
    
    do 
    {
        msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
            GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

        if (msg != NULL) {
            GError *err;
            gchar *debug_info;

            switch (GST_MESSAGE_TYPE (msg)) 
            {
                case GST_MESSAGE_ERROR:
                    gst_message_parse_error (msg, &err, &debug_info);
                    g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
                    g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
                    g_clear_error (&err);
                    g_free (debug_info);
                    terminate = TRUE;
                    break;

                case GST_MESSAGE_EOS:
                    g_print ("End-Of-Stream reached.\n");
                    terminate = TRUE;
                    break;
                
                case GST_MESSAGE_STATE_CHANGED:
                    if (GST_MESSAGE_SRC (msg) == GST_OBJECT (sender_data.pipeline)) 
                    {
                        GstState old_state, new_state, pending_state;
                        gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
                        
                        /*g_print ("Pipeline state changed from %s to %s:\n",
                            gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));*/
                        if (old_state == GST_STATE_PAUSED && new_state == GST_STATE_PLAYING)
                        {
                            g_print("Starting screen_sharing to %s.", target_ip);
                        }
                    }
                    break;
                default:
                    g_printerr ("Unexpected message received.\n");
                    break;
            }
            
            gst_message_unref (msg);
        
        }
    } while (!terminate);


    gst_object_unref(bus);
    gst_element_set_state(sender_data.pipeline, GST_STATE_NULL);
    gst_object_unref(sender_data.pipeline);
    return;


}
/*
int main(int argc, char* argv[])
{
    g_print("Initializing GStreamer.\n");
    gst_init(NULL, NULL);

    Sender_Data sender_data;
    GstBus* bus;
    GstStateChange ret;
    GstMessage* msg;
    gboolean terminate = FALSE;

    // Source
    sender_data.source = gst_element_factory_make("v4l2src", "source");
    
    // Caps filter and params
    sender_data.caps_filter = gst_element_factory_make ("capsfilter", "capsfilter");
    g_object_set(sender_data.caps_filter, "caps", gst_caps_from_string("video/x-raw, width=640, height=480"), NULL);
    
    // Convert
    sender_data.convert = gst_element_factory_make("videoconvert", "convert");
    
    // Encoder and params
    sender_data.encoder = gst_element_factory_make("x264enc", "encoder");
    gint zerolatency = 0x00000004;  // Ref: https://gstreamer.freedesktop.org/documentation/x264/index.html?gi-language=c#GstX264EncTune
    gint bitrate = 1000;
    gint threads = 4;
    g_object_set(sender_data.encoder, "tune", zerolatency, NULL);
    g_object_set(sender_data.encoder, "bitrate", bitrate, NULL);
    g_object_set(sender_data.encoder, "byte-stream", TRUE, NULL);
    g_object_set(sender_data.encoder, "threads", threads, NULL);

    // Parser
    sender_data.parser = gst_element_factory_make("h264parse", "parser");
    
    // Pay
    sender_data.pay = gst_element_factory_make("rtph264pay", "pay");

    // Sink and params
    sender_data.sink = gst_element_factory_make("udpsink", "sink");
    g_object_set(sender_data.sink, "host", "192.168.1.4", NULL);
    g_object_set(sender_data.sink, "port", 5000, NULL);
    

    // empty pipeline
    sender_data.pipeline = gst_pipeline_new("pipeline");

    if (!sender_data.source || !sender_data.caps_filter ||
        !sender_data.convert || !sender_data.encoder ||
        !sender_data.parser || !sender_data.pay || !sender_data.sink)
    {
        g_print("Not all elements could be created.");
        gst_object_unref(sender_data.pipeline);
        return 1;
    }

    // Adding binaries
    gst_bin_add_many(GST_BIN(sender_data.pipeline),
                     sender_data.source,
                     sender_data.caps_filter,
                     sender_data.convert,
                     sender_data.encoder,
                     sender_data.parser,
                     sender_data.pay,
                     sender_data.sink,
                     NULL);

    // Linking elements
    if (!gst_element_link_many (sender_data.source,
                           sender_data.caps_filter,
                           sender_data.convert,
                           sender_data.encoder,
                           sender_data.parser,
                           sender_data.pay,
                           sender_data.sink,
                           NULL))
    {
        g_printerr ("Elements could not be linked.\n");
        gst_object_unref (sender_data.pipeline);
        return 1;
    }

    ret = gst_element_set_state(sender_data.pipeline, GST_STATE_PLAYING);

    if (ret == GST_STATE_CHANGE_FAILURE) 
    {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (sender_data.pipeline);
        return 1;
    } 

    bus = gst_element_get_bus(sender_data.pipeline);
    
    do 
    {
        msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
            GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

        if (msg != NULL) {
            GError *err;
            gchar *debug_info;

            switch (GST_MESSAGE_TYPE (msg)) 
            {
                case GST_MESSAGE_ERROR:
                    gst_message_parse_error (msg, &err, &debug_info);
                    g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
                    g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
                    g_clear_error (&err);
                    g_free (debug_info);
                    terminate = TRUE;
                    break;

                case GST_MESSAGE_EOS:
                    g_print ("End-Of-Stream reached.\n");
                    terminate = TRUE;
                    break;
                
                case GST_MESSAGE_STATE_CHANGED:
                    if (GST_MESSAGE_SRC (msg) == GST_OBJECT (sender_data.pipeline)) {
                        GstState old_state, new_state, pending_state;
                        gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
                        g_print ("Pipeline state changed from %s to %s:\n",
                            gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
                    }
                    break;
                default:
                    g_printerr ("Unexpected message received.\n");
                    break;
            }
            
            gst_message_unref (msg);
        
        }
    } while (!terminate);


    gst_object_unref(bus);
    gst_element_set_state(sender_data.pipeline, GST_STATE_NULL);
    gst_object_unref(sender_data.pipeline);
    return 0;


}
*/
