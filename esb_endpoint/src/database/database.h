
#ifndef DATABASE 
#define DATABASE 

#include<../esb/bmd_parser.h>

int routeId(char*, char* , char* );
char* transformKey(int );
char* transportKey(int );
char* transportValue(int );
char* transformValue(int );

#endif