#include<stdio.h>
#include "email.h"
#include <bmd_parser.h>
#include <esbfun.h>
#include <stdlib.h>
#include <../database/database.h>
#include <../adapter/transform.h>
#include <../adapter/transport.h>
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
     if(validate_xml_file(bmd)==0)
     {
         printf("..................calculating..............\n");
         int routeID=routeId(bmd->bmd_envelope->Sender,bmd->bmd_envelope->Destination,bmd->bmd_envelope->MessageType);
        // printf("transformKey:%s\n", transformKey(routeID));
        // printf("transform_Value=%s\n",transformValue(routeID)(routeID));
        //        printf("\n--------------assigning variables-----------------\n");
        //  char* transform_Key=transformKey(routeID);
        //  char* transform_Value=transformValue(routeID)(routeID);
        //  char* transport_Key=transportKey(routeID)(routeID);
        //  char* transport_Value=transportValue(routeID);
        //  printf("routeID:%d\n\ntransformKey:%s\ntransform_Value:%s\n transport_Key:%s\ntransport_Value:%s\n\n",routeID, transform_Key,transform_Value,
        //    transport_Key ,transport_Value);
         printf("..................decision..............\n");
         //int result=decision(bmd,transformValue(routeID),transformKey(routeID),transportValue(routeID),transportKey(routeID)(routeID));
    // char* tfkey1="xml";
    // char* tfkey2=transformValue(routeID);
    // char* tpkey1=transportKey(routeID);
    // char* tpkey2=transportValue(routeID);
    // printf("\n\ntransport Value outside:%s\n\n",tpkey2);
    //  printf("\n\ntransform Value outside:%s\n\n",tfkey2);
    //   printf("\n\ntransport key outside:%s\n\n",tpkey1);


    char* address=transform(transformValue(routeID),bmd);
    
    if(transport(transportKey(routeID),address,routeID)==2)
    {
        toAddress(transportValue(routeID),address);
    }
    else if(transport(transportKey(routeID),address,routeID)==1)
    {
        tohttp(transportValue(routeID),address);
    }
    
    //  }
    // //      if(result==0)
    // //      {
    // //          printf("---------------------------SUCCESS---------------------------");
    // //      }

         return 0;
     }
     else
     {
         printf("BMD validation failed\n");
         return 1;
     }
    //return 0;
    // xml2json((char*)bmd->bmd_payload->data);

    // if(requestWeb()==0)
    // printf("Data send to web:SUCCESS\n");
    // else
    // {
    //     printf("Data send to web:FAILED\n");
    // }


    //  printf("......................As per the ID sending email...................\n");


    //  if(sendMail((char*)bmd->bmd_envelope->Destination,"/home/pc/Desktop/git/raavi_altered/raavi/esb_endpoint/Payload.json")==0)
    //  printf("success mail sent.....................................\n");
    //  else
    //  {
    //      printf("mail sending failed......................................\n");
    //  }


     return f_status;
}

