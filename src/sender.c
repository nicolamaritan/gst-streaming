#include "../include/screen.h"
#include "../include/sender_parse.h"

int main(int argc, char* argv[])
{
    Arguments args;
    if (parse_arguments(&args, argc, argv) != 0)
    {
        g_print("Argument option error.\n");
        return 1;
    }
    
    // GStreamer initialization
    gst_init(&argc, &argv);

    launch_screen_sender(args.receiver_ip);

    
    
    
}
