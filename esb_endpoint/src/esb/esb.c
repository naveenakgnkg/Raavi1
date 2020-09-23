#include<stdio.h>
#include "email.h"
#include <bmd_parser.h>
#include <esbfun.h>
#include <stdlib.h>
#include <../database/database.h>
#include <../adapter/transform.h>
#include <../adapter/transport.h>
//BMD* b;
/**
 * This is the main entry point into the ESB.
 * It will start processing of a BMD received at the HTTP endpoint.
 */

char* transform(char* tvalue,BMD* bmd)
{
    char* address;

      if(strcmp(tvalue,"xml")==0)
    {
        printf("-----------xml------------\n");
        address = payloadToXml(bmd);
        printf("address:%s\n",address);
    }
    if(strcmp(tvalue,"json")==0)
    {
        printf("-----------json------------\n");
        printf("tvalue:%s\n",tvalue);
        address= payloadToJson(bmd);
        printf("address:%s\n",address);
    }
    return address;
}

void toAddress(char* to,char* address)
{
    printf("------------------Send mail to:%s from:%s\n",to,address);
    sendMail(to,address);
    
}
void tohttp(char* to,char* address)
{
    printf("------------------Send http to:%s from:%s\n",to,address);
    requestWeb(to,address);
    
}

int transport(char* tkey,char* address,int routeID){
  
    if(strcmp(tkey,"mail")==0)
    {
        printf("-----------mail------------\n");
        return 2;
        printf("to:%s address:%s\n",routeID,address);
        
       
    }
    if(strcmp(tkey,"url")==0)
    {
        printf("-----------http------------\n");
        return 1;
        
       // printf("transportvalue:%s address:%s\n",transportvalue,address);
    }
    else
    {
        printf("-------------tkey:%s--------------- \n",tkey);
        return -1;
    }
    
}

int ttfunc(BMD* b)
{
         //printf("..................calculating..............\n");
         int routeID=routeId(b->bmd_envelope->Sender,b->bmd_envelope->Destination,b->bmd_envelope->MessageType);

         //printf("..................decision..............\n");

        char* address=transform(transformValue(routeID),b);
        
        if(transport(transportKey(routeID),address,routeID)==2)
        {
            toAddress(b->bmd_envelope->Destination,address);
        }
        else if(transport(transportKey(routeID),address,routeID)==1)
        {
            tohttp(transportValue(routeID),"https://reqres.in/api/users");
        }

        return 0;
}




int process_esb_request(char* bmd_file_path) {
    int f_status = 0; // OK == 0
    printf("Handling the BMD %s\n", bmd_file_path);
    /** TODO:
     * Perform the steps outlined in the Theory of Operation section of
     * the ESB specs document. Each major step should be implemented in
     * a separate module. Suitable unit tests should be created for all
     * the modules, including this one.
     */


    BMD *bmd=processXML(bmd_file_path);

     printf("BMD retrieved\n");
     if(validate_xml_file(bmd,bmd_file_path)==0)
     {
         //b=bmd;
         
        return 0;
     }
     else
     {
         printf("BMD validation failed\n");
         return 1;
     }

     return f_status;
}

