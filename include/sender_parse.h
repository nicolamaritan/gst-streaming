#ifndef PARSE
#define PARSE

typedef struct _Arguments
{
    char* receiver_ip;
} Arguments;

int flag_has_argument(int i, int argc, char* argv[]);
int parse_arguments(Arguments* args, int argc, char* argv[]);

#endif