#include "sender_parse.h"
#include <string.h>
#include <stdio.h>

int flag_has_argument(int i, int argc, char* argv[])
{
    // If it is not the last or above and if the next arg first char is not the dash -> true
    return i < argc - 1 && argv[i + 1][0] != '-';
    
}

int parse_arguments(Sender_Arguments* args, int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {  
        char* curr = argv[i];
        
        // Receiver ip flag
        if (strcmp("-i", curr) == 0)
        {
            if (!flag_has_argument(i, argc, argv))
                return 1;
            args->receiver_ip = argv[i+1];
            
        }
    }

    return 0;
}