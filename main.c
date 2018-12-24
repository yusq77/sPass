/*  Copyright (C) 2018 * Ltd. All rights reserved.
 *      Create date : 2018-11-05 15:46:47
 *================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"
#include "unionenc.h"

static char *pwd =NULL;
static int type;

void Usage()
{
	printf("-t [type] -s [pwd]\n");
	exit(-1);
}

void parse_arg( int argc, char **argv )
{
    int opt;
    extern char *optarg;

    while ((opt = getopt(argc,argv,"t:p:")) != -1)
    {
        switch(opt)
        {
            case 't':
                type = atoi(optarg);
                break;
            case 'p':
                pwd =strdup(optarg);
                break;
            default:
                Usage();
        }
    }

    if(type)
        printf("[type]: %d  <---- encrypt ---->  [pwd]: %s\n\n", type, pwd);
    else
        printf("[type]: %d  <---- decrypt ---->  [pwd]: %s\n\n", type, pwd);
}

void dec_enc(int type)
{
    if(type == 0)
    {
        decrypt(pwd);// decrypt
    }
    else
    {
        switch(type)
        {
            case 1:
                encrypt(pwd);// encrypt
                break;
            default:
                Usage();
        }
    }

}

int main(int argc, char **argv)
{

    parse_arg(argc, argv);
    dec_enc(type);

    return 0;
}
