// compiling: gcc -Wall $(xml2-config --cflags) $(xml2-config --libs) -o xmlParse xmlParse.c -lxml2

#include <stdio.h>
#include <string.h>
#include"function.h"
#include <libxml/parser.h>
#include <libxml/tree.h>

void printValues(char** array,char** value,int size)
{
    for(int i=0;i<=size;i++)
    {
        printf("%d: name->%s value->%s\n",i,array[i],value[i]);
    }
    printf("\n");
}

int readXml(char* nameXML)
{
    //xml tree parameters
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node,*temp;
    char           *filename;
    
    //xml file name
    filename = nameXML;
    //reading xml file
    document = xmlReadFile(filename, NULL, 0);
    temp = xmlDocGetRootElement(document);
    root=xmlFirstElementChild(temp);
    

    //reading values from xml and saving in array
        char* arrayName[8];
        char* arrayValue[8];
        int i=0;
        //accessing first member in xml tree
        first_child = root->children;
        //all the siblings of first member
        for (node = first_child; node; node = node->next) {
            if(node->type==1)
            {
                //inserting values in array
                arrayName[i]=(char*)node->name;
                arrayValue[i]=(char*)xmlNodeGetContent(node);
                i++;
            }
        }
    //Accessing Payload 
    root=xmlLastElementChild(temp);
    first_child = root;
        for (node = first_child; node; node = node->next) {
            if(node->type==1)
            {
                arrayName[i]=(char*)node->name;
                arrayValue[i]=(char*)xmlNodeGetContent(node);
                i++;
            }
        }
    //size of array
    int size = sizeof arrayName / sizeof arrayName[0];
    //check xml values in array
    printValues(arrayName,arrayValue,size);
    return 0;
}
