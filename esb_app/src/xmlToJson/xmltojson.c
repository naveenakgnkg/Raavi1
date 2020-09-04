#include<stdio.h>
#include<stdlib.h>

void xml2json(char* payloadArray)
{
	//creating Payload.json file
	char filename[] = "Payload.json";
        FILE *file;
    	file = fopen(filename,"w");
    	
    	if(file == NULL) 
    	{
        	printf("file write failed");
        	exit(0);
    	}
    	
    	//writing in json file
    	fprintf(file,"{\n \"Payload\":\"%s\"\n}",payloadArray);
    	
    	printf("\nSuccess Payload json File created\n");
    	fclose(file);
    	return NULL;
}
