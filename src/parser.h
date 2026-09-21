#ifndef PARSER 
#define PARSER

typedef struct{
    char tokens[64][1024];
    int tok_count;
    int trait;
} CMD_SQ;

CMD_SQ *parse(char tokens[], int *length, char delim[]);
#endif