#ifndef BMD3_H
#define BMD3_H
//#include "xml_handler2.c"

/*static envelope *get_envelope_struct()
{
    envelope *bmd_envelope = (envelope *)malloc(sizeof(envelope));
    return bmd_envelope;
}

static payload *get_payload_struct()
{
    payload *bmd_payload = (payload *)malloc(sizeof(payload));
    return bmd_payload;
}*/

typedef struct
{
  const unsigned char *key;
  void *value;
} pair;
//bmd envelope
typedef struct
{
  const unsigned char *MessageID;
  const unsigned char *MessageType;
  const unsigned char *Sender;
  const unsigned char *Destination;
  const unsigned char *CreationDateTime;
  const unsigned char *Signature;
  pair *UserProperties[50];
  const unsigned char *ReferenceID;

} envelope;

typedef struct
{
  const unsigned char *data;
} payload;

//complete BMD
typedef struct 
{
  envelope *bmd_envelope;
  payload *bmd_payload;
}BMD;




 void print(BMD *bmd)
 {
 	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
     
    bmd->bmd_envelope->MessageID,
    bmd->bmd_envelope->MessageType,
    bmd->bmd_envelope->Destination,
    bmd->bmd_envelope->CreationDateTime,
    bmd->bmd_envelope->ReferenceID,
    bmd->bmd_envelope->Sender,
    bmd->bmd_envelope->Signature,
    bmd->bmd_envelope->UserProperties,
    bmd->bmd_payload->data
     
     );
 }

BMD* processXML(char* nameXML)
{
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node,*temp;
    char           *filename;
    
    BMD *bmd = (BMD *)(malloc(sizeof(BMD *)));

    bmd->bmd_envelope = (envelope *)malloc(sizeof(envelope));
    bmd->bmd_payload = (payload *)malloc(sizeof(payload));




    filename = nameXML;
    
    document = xmlReadFile(filename, NULL, 0);
    temp = xmlDocGetRootElement(document);
    root=xmlFirstElementChild(temp);
  
        char* arrayName[8];
        char* arrayValue[8];
        int i=0;
        first_child = root->children;
        for (node = first_child; node; node = node->next) {
            // if(node->type==1)
            // fprintf(stdout, "\t Child is <%s>  (%i) value: \n", node->name ,node->type);
            // // temp=node;

            if(node->type==1)
            {
            // printf("%d\n",checkNamespace("MessageID",node->name));
                arrayName[i]=(char*)node->name;
                
                arrayValue[i]=(char*)xmlNodeGetContent(node);
                //fprintf(stdout, "attributes:<%s>\tvalue: %s\n", node->name,xmlNodeGetContent(node));
               // printf("%d: name->%s value->%s\n",i,arrayName[i],arrayValue[i]);
                i++;
            }
        }
        bmd->bmd_envelope->MessageID=(unsigned char*)arrayValue[0];
    bmd->bmd_envelope->MessageType=(unsigned char*)arrayValue[1];
    bmd->bmd_envelope->Destination=(unsigned char*)arrayValue[3];
    bmd->bmd_envelope->CreationDateTime=(unsigned char*)arrayValue[4];
    bmd->bmd_envelope->ReferenceID=(unsigned char*)arrayValue[6];
    bmd->bmd_envelope->Sender=(unsigned char*)arrayValue[2];
    bmd->bmd_envelope->Signature=(unsigned char*)arrayValue[5];
    //bmd->bmd_envelope->UserProperties=(unsigned char*)arrayValue[7];
    //bmd->bmd_payload->data=(unsigned char*)arrayValue[8];
  

    root=xmlLastElementChild(temp);
    first_child = root;
        for (node = first_child; node; node = node->next) {
            // if(node->type==1)
            // fprintf(stdout, "\t Child is <%s>  (%i) value: \n", node->name ,node->type);
            // // temp=node;

            if(node->type==1)
            {
            // printf("%d\n",checkNamespace("MessageID",node->name));
                arrayName[i]=(char*)node->name;
                arrayValue[i]=(char*)xmlNodeGetContent(node);
                //fprintf(stdout, "attributes:<%s>\tvalue: %s\n", node->name,xmlNodeGetContent(node));
                printf("%d: name->%s value->%s\n",i,arrayName[i],arrayValue[i]);
                i++;
            }
        }
        bmd->bmd_payload->data=(unsigned char*)arrayValue[8];
    // }
    //int size = sizeof arrayName / sizeof arrayName[0];
    // for(int i=0;i<=size;i++)
    // {
    //     printf("%d: name->%s value->%s\n",i,arrayName[i],arrayValue[i]);
    // }
    
    //xml2json(bmd->bmd_payload->data);
    //print(bmd);
    return(bmd);
}


char xml2json(char* payloadArray)
{
	char filename[] = "Payload.json";
        FILE *file;
    	file = fopen(filename,"w");
    	
    	if(file == NULL) 
    	{
        	printf("file opening filed");
        	exit(0);
    	}
    	//printf("\nparsed xml to json\n");
    	//write payload with json formate
		//printf("{\n \"Payload\":\"%s\"\n}",payloadArray);
    	fprintf(file,"{\n \"Payload\":\"%s\"\n}",payloadArray);
		//confirmation message
    	//printf("\nPayload json File created\n");
    	fclose(file);
    	// returns json filename 
    	return strdup(filename);
}
//void insert_to_routes(char **sender,char **destination,char **message_type,char **is_active);
//char * extract_payload(char * filepath);

//void insert_to_routes(char **sender,char **destination,char **message_type,char **is_active);

  int validate_xml_file( BMD * bmd_file)
{
  /* MessageID */
 //printf("\n%s in h\n",arrayValue[7]);
  if(strcmp(bmd_file->bmd_envelope->MessageID ,"" )==0) {
    fprintf(stderr,"Message ID doesnot exist in bmd");
    return 0;
  }

  /* MessageType */
  if(strcmp(bmd_file->bmd_envelope->MessageType ,"") ==0){
    fprintf(stderr,"Message Type doesnot exist in bmd");
    return 0;
  }

  /* Sender */
  if(strcmp(bmd_file->bmd_envelope->Sender,"")==0) {
    fprintf(stderr,"Sender doesnot exist in bmd\n");
    return 0;
  }


  /* Destination */
  if(strcmp(bmd_file->bmd_envelope->Destination ,"")==0 ){
    fprintf(stderr,"Destination doesnot exist in bmd");
    return 0;
  }


  /* CreationDateTime */
  if(strcmp(bmd_file->bmd_envelope->CreationDateTime ,"")==0) {
    fprintf(stderr,"CreationDateTime doesnot exist in bmd");
    return 0;
  }


  /* Signature */
  if(strcmp(bmd_file->bmd_envelope->Signature ,"")==0) {
    fprintf(stderr,"Signature doesnot exist in bmd");
    return 0;
  }

  /* ReferenceID */
  if(strcmp(bmd_file->bmd_envelope->ReferenceID , "")==0 ){
      fprintf(stderr,"ReferenceID doesnot exist in bmd");
      return 0;
  }

  /* payload */
  if(strcmp(bmd_file->bmd_payload->data , "")==0) {
    fprintf(stderr,"Payload doesnot exist in bmd");
    return 0;
  }

  return 1;
}

 #endif
