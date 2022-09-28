#include "receiver_screen.h"

static void pad_added_handler(GstElement* src, GstPad* new_pad, Screen_Receiver_Data* data)
{
    GstPad* sink_pad = gst_element_get_static_pad(data->convert, "sink");
    g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));


    /* Attempt the link */
    GstPadLinkReturn ret = gst_pad_link (new_pad, sink_pad);
}

void init_screen_receiver_data(Screen_Receiver_Data* data)
{
    // gst-launch-1.0 -v udpsrc port=5000 caps="application/x-rtp,media=(string)video,encoding-name=(string)H264,payload=(int)96" ! rtpjitterbuffer ! rtph264depay ! decodebin ! videoconvert ! queue ! autovideosink

    // empty pipeline
    data->pipeline = gst_pipeline_new("receiver-pipeline");

    // Source
    data->source = gst_element_factory_make("udpsrc", "source");
    g_object_set(data->source, "port", 5000, NULL);

    GstCaps* udpcaps = gst_caps_new_simple("application/x-rtp",
        //"media", G_TYPE_STRING, "video",
        //"clock-rate", G_TYPE_INT, 9000,
        //"encoding-name", G_TYPE_STRING, "H264",
        //"payload", G_TYPE_INT, 96,
        NULL);

    g_object_set(G_OBJECT(data->source), "caps", udpcaps , NULL);

    // Buffer - Reorders and removes duplicate RTP packets from udpsrc
    data->buffer = gst_element_factory_make("rtpjitterbuffer", "buffer");
    
    // Depay - Extracts H264 video from RTP packets
    data->depay = gst_element_factory_make("rtph264depay", "depay");

    // Decode
    data->decoder = gst_element_factory_make("decodebin", "decoder");

    // Convert
    data->convert = gst_element_factory_make("videoconvert", "convert");
    
    // Queue
    data->queue = gst_element_factory_make("queue", "queue");

    // Sink
    data->sink = gst_element_factory_make("autovideosink", "sink");
}

void launch_screen_receiver()
{
    Screen_Receiver_Data receiver_data;
    GstBus* bus;
    GstStateChangeReturn ret;
    GstMessage* msg;
    gboolean terminate = FALSE;

    init_screen_receiver_data(&receiver_data);

    // Adding binaries
    gst_bin_add_many(GST_BIN(receiver_data.pipeline),
                     receiver_data.source,
                     receiver_data.buffer,
                     receiver_data.depay,
                     receiver_data.decoder,
                     receiver_data.convert,
                     receiver_data.queue,
                     receiver_data.sink,
                     NULL);


    // Link first part of the pipeline, excluding decoder ! convert
    if (!gst_element_link_many (receiver_data.source,                       
                                receiver_data.buffer,                  
                                receiver_data.depay,
                                receiver_data.decoder,
                                NULL))
    {
        g_printerr ("Elements could not be linked.\n");
        gst_object_unref (receiver_data.pipeline);
        return;
    }
    // Link second part of the pipeline
    if (!gst_element_link_many (receiver_data.convert,
                                receiver_data.queue,
                                receiver_data.sink,
                                NULL))
    {
        g_printerr ("Elements could not be linked.\n");
        gst_object_unref (receiver_data.pipeline);
        return;
    }

    /* Decodebin has a sometimes-src, therefore it must be connected dynamically through
    a callback function. Ref: https://gstreamer.freedesktop.org/documentation/tutorials/basic/dynamic-pipelines.html?gi-language=c*/
    g_signal_connect(receiver_data.decoder, "pad-added", G_CALLBACK(pad_added_handler), &receiver_data);
    
    

    ret = gst_element_set_state(receiver_data.pipeline, GST_STATE_PLAYING);

    if (ret == GST_STATE_CHANGE_FAILURE) 
    {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (receiver_data.pipeline);
        return;
    } 

    g_print("Looking for a sender.");
    bus = gst_element_get_bus(receiver_data.pipeline);
    
    do 
    {
        // Getting message from the bus
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
                    terminate = TRUE;   // If error exits.
                    break;

                case GST_MESSAGE_EOS:
                    g_print ("End-Of-Stream reached.\n");
                    terminate = TRUE;   // If end of stream exits.
                    break;
                
                case GST_MESSAGE_STATE_CHANGED:
                    if (GST_MESSAGE_SRC (msg) == GST_OBJECT (receiver_data.pipeline)) 
                    {
                        GstState old_state, new_state, pending_state;
                        gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
                        
                        /*g_print ("Pipeline state changed from %s to %s:\n",
                            gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));*/
                        if (old_state == GST_STATE_PAUSED && new_state == GST_STATE_PLAYING)
                        {
                            g_print("Sender found.");
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
    gst_element_set_state(receiver_data.pipeline, GST_STATE_NULL);
    gst_object_unref(receiver_data.pipeline);
    return;    
}

