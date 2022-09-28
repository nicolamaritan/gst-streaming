#ifndef RECEIVER_PARSE_H
#define RECEIVER_PARSE_H

typedef struct _Receiver_Arguments
{
    
} Receiver_Arguments;

int flag_has_argument(int i, int argc, char* argv[]);
int parse_arguments(Receiver_Arguments* args, int argc, char* argv[]);

#endif