#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "bmd_parser.h"

int isEnd(xmlNode * node)
{
  xmlNode * child = node->children;
  while(child)
  {
    if(child->type == XML_ELEMENT_NODE) return 0;
    child = child->next;
  }
  return -1;
}


/*
*for debuging

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

*/

BMD* parse(xmlNode * node,BMD * b)
{
    int len;
    while(node!=NULL)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
            if(isEnd(node))
            {     
                  /* Extracting MessageID*/
                 len= strlen((char*) xmlNodeGetContent(node));
                
                if((strcmp(((char *) node->name),"MessageID"))==0)
                {
                    b->bmd_envelope->MessageID= malloc((len+1)* sizeof(char));
                    strcpy(b->bmd_envelope->MessageID,(char *) xmlNodeGetContent(node));
                   
                }
                /* Extracting MesageType*/
                else if((strcmp(((char *) node->name),"MessageType"))==0)
	              {
	            b->bmd_envelope->MessageType =  (char *)malloc((len+1)* sizeof(char));
                    strcpy(b->bmd_envelope->MessageType ,(char *)xmlNodeGetContent(node));
                  
	              }
                /* Extracting Sender*/
                else if(strcmp(((char *) node->name), "Sender")==0)
	              {
		    b->bmd_envelope->Sender =  (char *)malloc((len+1)* sizeof(char));
                   strcpy(b->bmd_envelope->Sender ,(char *)xmlNodeGetContent(node));
                 
	            	 }
                 /* Extracting Destination*/
                else if((strcmp(((char *) node->name),"Destination"))==0)
                {
		    b->bmd_envelope->Destination =  (char *)malloc((len+1)* sizeof(char));
                   strcpy(b->bmd_envelope->Destination ,(char *)xmlNodeGetContent(node));
                 
	              }
                /* Extracting CreationDateTime*/
                else if((strcmp(((char *) node->name),"CreationDateTime"))==0)
	              {
		    b->bmd_envelope->CreationDateTime =  (char *)malloc((len+1)* sizeof(char));
                   strcpy(b->bmd_envelope->CreationDateTime ,(char *)xmlNodeGetContent(node));
                
	               }
                 /* Extracting Signature*/
	              else  if((strcmp(((char *) node->name),"Signature"))==0)
            	  {
         	    b->bmd_envelope->Signature =  (char *)malloc((len+1)* sizeof(char));
                   strcpy(b->bmd_envelope->Signature ,(char *)xmlNodeGetContent(node));
                   
                }
                /* Extracting ReferenceID*/
                else if((strcmp(((char *) node->name),"ReferenceID"))==0)
	              {
		    b->bmd_envelope->ReferenceID =  (char *)malloc((len+1)* sizeof(char));
                    strcpy(b->bmd_envelope->ReferenceID ,(char *)xmlNodeGetContent(node));
                
                }
                
                else if((strcmp(((char *) node->name),"Payload"))==0)
	              {
		    b->bmd_payload->data=  (char *)malloc((len+1)* sizeof(char));
                    strcpy(b->bmd_payload->data,(char *)xmlNodeGetContent(node));
                
                }
            }
        }
        parse(node->children,b);
        node = node->next;
    }
    return b;
}

/**
 * Simple example to parse a file called "file.xml", 
 * walk down the DOM, and print the name of the 
 * xml elements nodes.
 */
BMD* processXML(char* nameXML)
{
    xmlDoc         *doc = NULL;
    xmlNode        *root_element = NULL;
    
    BMD *bmd = (BMD *)(malloc(sizeof(BMD *)));

    bmd->bmd_envelope = get_envelope_struct();
    bmd->bmd_payload = get_payload_struct();

    /*parse the file and get the DOM */
    doc = xmlReadFile(nameXML, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", nameXML);
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);
    printf("printing bmd values....................\n");
    bmd=parse(root_element, bmd);
    printf("%s\n",bmd->bmd_envelope->Sender);
    printf("%s\n",bmd->bmd_envelope->Destination);
   // print(bmd);
    return bmd;
    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

   
}

/*int main()
{

    processXML("/home/harshal/Desktop/bmd.xml");
}
*/
