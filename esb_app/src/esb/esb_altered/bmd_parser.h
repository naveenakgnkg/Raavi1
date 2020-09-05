#define START_TAG 1 //value acoording to return type of xmlTextReaderNodeType
#define END_TAG 15 //value acoording to return type of xmlTextReaderNodeType
//pair structure for UserProperties
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

BMD *processXML(char *);

