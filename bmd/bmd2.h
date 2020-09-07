#ifndef XML_H
#define XML_H
//#include "routes.c"

typedef struct 
{
    char  *MessageID;
    char  *MessageType;
    char  *Sender;
    char * Destination;
    char *CreationDateTime;
    char  *Signature;
    char  *ReferenceID;
}bmd_envelope;


typedef struct 
{
  bmd_envelope * envelope;
  char * Payload;
} bmd;



bmd_envelope *  extract_envelope(char * filepath);
//void insert_to_routes(char **sender,char **destination,char **message_type,char **is_active);
char * extract_payload(char * filepath);
int validate_xml_file (bmd * bmd_file);
//void insert_to_routes(char **sender,char **destination,char **message_type,char **is_active);

 

 #endif
