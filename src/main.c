#include "../include/screen.h"

int main(int argc, char* argv[])
{
    // If no additional argument (program excluded)
    if (argc == 1)
    {
        g_print("Not enough arguments. Exiting 1.\n");
        return 1;
    }

    char* role = argv[1];
    
    // GStreamer initialization
    gst_init(&argc, &argv);
    
    if (strcmp(role, "sender") == 0)
    {
        launch_screen_sender("127.0.0.1");
    }

    
    
    
}
