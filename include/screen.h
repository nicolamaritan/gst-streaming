#ifndef SCREEN_H
#define SCREEN_H

#include <gst/gst.h>

typedef struct _Screen_Sender_Data
{
    GstElement* pipeline;

    GstElement* source;
    GstElement* caps_filter;
    GstElement* convert;
    GstElement* encoder;
    GstElement* parser;
    GstElement* pay;
    GstElement* sink;

} Screen_Sender_Data;

void launch_screen_sender(gchar* target_ip);
void init_screen_sender_data(Screen_Sender_Data* data, gchar* target_ip);

#endif