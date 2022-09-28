#include "receiver_screen.h"
#include "receiver_parse.h"

int main(int argc, char* argv[])
{
    /*Receiver_Arguments args;
    if (parse_arguments(&args, argc, argv) != 0)
    {
        g_print("Argument option error.\n");
        return 1;
    }*/
    
    // GStreamer initialization
    gst_init(&argc, &argv);

    launch_screen_receiver();

    
    
    
}
