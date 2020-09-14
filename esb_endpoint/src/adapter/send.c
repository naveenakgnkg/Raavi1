#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../esb/bmd_parser.h"
#include <../database/database.h>

void decision(char* transformvalue,char* transformkey,char* transportvalue,char* transportkey)
{
    char* tfkey1="xml";
    char* tfkey2="json";
    char* tpkey1="email";
    char* tpkey2="http";
    if(strcmp(transformvalue,tfkey1)==0)
    {

    }
    else if(strcmp(transformvalue,tfkey2)==0)
    {
        
    }

    if(strcmp(transportvalue,tpkey1)==0)
    {

    }
    else if(strcmp(transportvalue,tpkey2)==0)
    {
        
    }
}