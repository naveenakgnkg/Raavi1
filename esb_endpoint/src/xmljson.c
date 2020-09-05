#include<stdio.h>
#include<stdlib.h>

void xml2json(char* payloadArray)
{
	char filename[] = "Payload.json";
        FILE *file;
    	file = fopen(filename,"w");
    	
    	if(file == NULL) 
    	{
        	printf("file opening filed");
        	exit(0);
    	}
    	printf("\nparsed xml to json\n");
    	//write payload with json formate
		printf("{\n \"Payload\":\"%s\"\n}",payloadArray);
    	fprintf(file,"{\n \"Payload\":\"%s\"\n}",payloadArray);
		//confirmation message
    	printf("\nPayload json File created\n");
    	fclose(file);
    	// returns json filename 
    	return strdup(filename);
}
