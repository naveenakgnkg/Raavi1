#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <bmd_parser.h>

int validate_xml_file( BMD * bmd_file)
{
  /* MessageID */
  if(bmd_file->bmd_envelope->MessageID == NULL) {
    fprintf(stderr,"Message ID doesnot exist in bmd");
    return 0;
  }

  /* MessageType */
  if(bmd_file->bmd_envelope->MessageType == NULL) {
    fprintf(stderr,"Message Type doesnot exist in bmd");
    return 0;
  }

  /* Sender */
  if(bmd_file->bmd_envelope->Sender == NULL) {
    fprintf(stderr,"Sender doesnot exist in bmd");
    return 0;
  }


  /* Destination */
  if(bmd_file->bmd_envelope->Destination== NULL) {
    fprintf(stderr,"Destination doesnot exist in bmd");
    return 0;
  }


  /* CreationDateTime */
  if(bmd_file->bmd_envelope->CreationDateTime == NULL) {
    fprintf(stderr,"CreationDateTime doesnot exist in bmd");
    return 0;
  }


  /* Signature */
  if(bmd_file->bmd_envelope->Signature == NULL) {
    fprintf(stderr,"Signature doesnot exist in bmd");
    return 0;
  }

  /* ReferenceID */
  if(bmd_file->bmd_envelope->ReferenceID == NULL) {
      fprintf(stderr,"ReferenceID doesnot exist in bmd");
      return 0;
  }

  /* payload */
  if(bmd_file->bmd_payload->data == NULL) {
    fprintf(stderr,"Payload doesnot exist in bmd");
    return 0;
  }

  return 1;
}

/* for testing:
int main()
{
    char  filepath[50];
    scanf("%s",filepath);
    bmd  * bd = (bmd*) malloc (sizeof(bmd));
    validate_xml_file(bd)? printf("1"): printf("2");
    printf("\n");
    return 0;
}
*/