#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void var_value(char array[9][100])
{
    
	for(int i=0;i<9;i++)
	{
        char start1[]="<";
	    char start2[]="</";
	    char ending[]=">";
        char *p=*(array +i);
		strcat(p,ending);
		strcat(start1,p);
		//strcat(start2,p);
		printf("start=%s \t ending:%s",start1,start2);
        
       //strcat(array+i,ending);
       printf("\n%s \n",*(array+i));
		//list[1][i]=parse(*xml,start,endtag);
	}
    
	
	
}


void charList(char array[9][100])
{
    for(int i=0;i<9;i++)
    {
        printf("string = %s \n", *(array + i));
    }
}

int main()
{
    char array[9][100]={"MessageID","MessageType",
    "Sender","Destination","CreationDateTime",
    "Signature","ReferenceID","key1","key2"};
    //charList(array);

    //var_value(array);
    for(int i=0;i<9;i++)
    {
        char start1[][]="<";
	    char start2[][]="</";
	    char ending[][]=">";
        char p[][]=" ";
        strcat(p,array +i);
        strcat(p,ending);
        printf("p:%s\t",p);
        strcat(start1,p);
        printf("start1:%s\t",start1);
        strcat(start2,p);
        printf("start2:%s\t",start2);
    }
    //strcat(array+1,array+3);
    //printf("%s\n",array+1);
    /*
    for(int i = 0; i < 9; i++)
    {
        printf("string = %s \n", array + i);
    }
    
    return 0;
}
*/

char* pass(char *xml, char *s1, char *s2)
{
    char *var;
    var = strstr(xml, s1);
    int startIndex = strlen(xml) - strlen(var) + strlen(s1);
    var = strstr(xml, s2);
    int endIndex = strlen(xml) - strlen(var);
    int diff=endIndex-startIndex;
    printf("start: %d\nend: %d\ndiff:%d\n",startIndex,endIndex,diff);
    char value[diff];
    char *p = (char *)malloc(sizeof(char) * (diff));
    strncpy(value, xml + startIndex, diff);
    //printf("\n%s\n",xml + startIndex);
    printf("%s\n",value);
    //char* p;
    strcpy(p,value);
    return p;
}
// printf("%s",var);
// char* p = strstr(xml, s2);
// printf("%s",xml);
// // Prints the result
// if (p) {
//     strcpy(p," ");
//     //printf("%s", s1);
// } else
//     {
//         printf("Value not found\n");
//         //return exit(0);
//     }

// char* value=strstr(var,">");

// return value;

//}

int main()
{
    char v[100];
    char xml[1000];
    char *MessageId;
    char *MessageType;
    char *Sender;
    char *Destination;
    char *CreationDateTime;
    char *Signature;
    char *ReferenceID;
    char*key1;
    char*key2;
    char *Payload;
    
    strcpy(xml, " ");
    FILE *file;
    file = fopen("bmd.xml", "r");
    while (fgets(v, sizeof(v), file) != NULL)
    {
        strcat(xml, v);
    }
    fclose(file);
    char s1[] = "<MessageID>";
    char s2[] = "</MessageID>";
    MessageId = pass(xml, s1, s2);
    printf("MessageId = %s\n", MessageId);

    char s3[] = "<MessageType>";
    char s4[] = "</MessageType>";
    MessageType = pass(xml, s3, s4);
    printf("MessageType = %s\n", MessageType);

    char s5[] = "<Sender>";
    char s6[] = "</Sender>";
    Sender = pass(xml, s5, s6);
    printf("Sender = %s\n", Sender);

    char s7[] = "<Destination>";
    char s8[] = "</Destination>";
    Destination = pass(xml, s7, s8);
    printf("Destination = %s\n", Destination);

    char s9[] = "<CreationDateTime>";
    char s10[] = "</CreationDateTime>";
    CreationDateTime = pass(xml, s9, s10);
    printf("CreationDateTime = %s\n", CreationDateTime);

    char s11[] = "<Signature>";
    char s12[] = "</Signature>";
    Signature = pass(xml, s11, s12);
    printf("Signature = %s\n", Signature);

    char s13[] = "<ReferenceID>";
    char s14[] = "</ReferenceID>";
    ReferenceID = pass(xml, s13, s14);
    printf("ReferenceID = %s\n", ReferenceID);

    char s15[] = "<key1>";
    char s16[]= "</key1>";
    key1 = pass(xml, s15, s16);
    printf("key1 = %s\n", key1);

    char s17[] = "<key2>";
    char s18[]= "</key2>";
    key1 = pass(xml, s17, s18);
    printf("key2 = %s\n", key2);

    char s19[] = "<Payload>";
    char s20[] = "</Payload>";
    Payload = pass(xml, s19, s20);
    printf("Payload = %s\n", Payload);

   
    return 0;
}
