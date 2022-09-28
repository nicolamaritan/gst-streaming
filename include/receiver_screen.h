#ifndef RECEIVER_SCREEN_H
#define RECEIVER_SCREEN_H

#include <gst/gst.h>

typedef struct _Screen_Receiver_Data
{
    GstElement* pipeline;

    GstElement* source;
    GstElement* buffer;
    GstElement* depay;
    GstElement* decoder;
    GstElement* convert;
    GstElement* queue;
    GstElement* sink;

} Screen_Receiver_Data;

void launch_screen_receiver();
void init_screen_receiver_data(Screen_Receiver_Data* data);


#endif