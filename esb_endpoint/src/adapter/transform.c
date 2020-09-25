#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include "../esb/bmd_parser.h"

char* payloadToJson(BMD* bmd)
{
    char filename[]="payload.json";
    //create jsonStore folder to save files
    //to make unique json file,add messageID
    //sprintf(filename, "../jsonStore/payload%s.json", bmd->bmd_envelope->MessageID);
    //Create file and format payload as JSON
    FILE *file;
 	file = fopen(filename,"w");
    if(file == NULL) 
    {
	printf("file opening filed");
	exit(0);
    }
    //write payload with json formate
    fprintf(file,"{\n \"Payload\":\"%s\"\n}",bmd->bmd_payload->data);
	//confirmation message
    printf("\nPayload json File created\n");
    fclose(file);
    // returns json filename 
    return strdup(filename);	
      
}

char* payloadToXml(BMD* bmd)
{
    char filename[]="pay.xml";
    //create XMLStore folder to save files
    //to make unique xml file, add messageID
   // sprintf(filename, "../XMLStore/payload%s.xml", bmd->bmd_envelope->MessageID);
    //Create file and format payload as JSON
    FILE *file;
 	file = fopen(filename,"w");
    if(file == NULL) 
    {
	printf("file opening filed");
	exit(0);
    }
    //write payload with json formate
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<?xml-stylesheet type='text/xsl'?>\n<payload>%s</payload>", bmd->bmd_payload->data);
    	
    printf("\nPayload XML File created\n");
    fclose(file);
    // returns json filename 
    return strdup(filename);	
    
}
