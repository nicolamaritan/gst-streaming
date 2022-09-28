#ifndef SENDER_PARSE_H
#define SENDER_PARSE_H

typedef struct _Sender_Arguments
{
    char* receiver_ip;
} Sender_Arguments;

int flag_has_argument(int i, int argc, char* argv[]);
int parse_arguments(Sender_Arguments* args, int argc, char* argv[]);

#endif