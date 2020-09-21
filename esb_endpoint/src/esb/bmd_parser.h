#define START_TAG 1 //value acoording to return type of xmlTextReaderNodeType
#define END_TAG 15 //value acoording to return type of xmlTextReaderNodeType
//pair structure for UserProperties
// typedef struct
// {
//   const unsigned char *key;
//   void *value;
// } pair;
//bmd envelope
#include<stdlib.h>
#include<stdio.h>
typedef struct
{
  const unsigned char *MessageID;
  const unsigned char *MessageType;
  const unsigned char *Sender;
  const unsigned char *Destination;
  const unsigned char *CreationDateTime;
  const unsigned char *Signature;
  const unsigned char *UserProperties;
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


static envelope *get_envelope_struct()
{
    envelope *bmd_envelope = (envelope *)malloc(sizeof(envelope));
    return bmd_envelope;
}

static payload *get_payload_struct()
{
    payload *bmd_payload = (payload *)malloc(sizeof(payload));
    return bmd_payload;
}

BMD *processXML(char *);
envelope *extract_envelop(char *bmd_xml);
payload *extract_payload(char *bmd_xml);

int sqlcon(BMD *bmd,char *bmdfileloc);
int requestWeb(char*request,char*address);
int sendMail(char*,char*);

int ttfunc(BMD* b);
