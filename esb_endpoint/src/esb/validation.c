#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <bmd_parser.h>

int validate_xml_file( BMD * bmd_file)
{
  /* MessageID */
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
