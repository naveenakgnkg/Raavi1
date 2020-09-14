#include<stdio.h>
#include "email.h"
#include <bmd_parser.h>
#include <esbfun.h>
#include <stdlib.h>
#include <../database/database.h>

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
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
         int routeID=routeId(bmd->bmd_envelope->Sender,bmd->bmd_envelope->Destination,bmd->bmd_envelope->MessageType);
         char* transform_Key=transformKey(routeID);
         char* transform_Value=transformValue(routeID);
         char* transport_Key=transportKey(routeID);
         char* transport_Value=transportValue(routeID);
         

         return 0;
     } 
     else
     {
         printf("BMD validation failed\n");
         return 1; 
     }
     
    xml2json((char*)bmd->bmd_payload->data);

    if(requestWeb()==0)
    printf("Data send to web:SUCCESS\n"); 
    else
    {
        printf("Data send to web:FAILED\n");
    }
     
     
     printf("......................As per the ID sending email...................\n");
     
     
     if(sendMail((char*)bmd->bmd_envelope->Destination,"/home/pc/Desktop/git/raavi_altered/raavi/esb_endpoint/Payload.json")==0)
     printf("success mail sent.....................................\n");
     else
     {
         printf("mail sending failed......................................\n");
     }
     
     
     return f_status;
}

