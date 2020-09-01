#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void finish_with_error(MYSQL *conn)
{
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(conn),mysql_errno(conn));
	mysql_close(conn);
	exit(1);
}

int main()
{
  //XML parsing code
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node,*temp;
    char           *filename;
    
    filename = "bmd.xml";

    document = xmlReadFile(filename, NULL, 0);
    temp = xmlDocGetRootElement(document);
    root=xmlFirstElementChild(temp);
  
        char* arrayName[8];
        char* arrayValue[8];
        int i=0;
        first_child = root->children;
        for (node = first_child; node; node = node->next) {
            if(node->type==1)
            {
                arrayName[i]=(char*)node->name;
                arrayValue[i]=(char*)xmlNodeGetContent(node);
                i++;
            }
        }

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
    //Parsed value output

    // int size = sizeof arrayName / sizeof arrayName[0];
    // for(int i=0;i<=size;i++)
    // {
    //     printf("%d: name->%s value->%s\n",i,arrayName[i],arrayValue[i]);
    // }
    

    // fprintf(stdout, "...\n");

//Adding to database
MYSQL *conn;

char *server = "localhost";
char *user = "root";
char *password = "root";
char *database = "esb_db";

conn = mysql_init(NULL);
if(! mysql_real_connect(conn, server, user, password,database,0,NULL,0))
{
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(conn),mysql_errno(conn));
	exit(1);
}
//Need to update esb_request table

// i-->ID
//arrayName[i]--> Parameters
//arrayValue[i]-->Values to be stored 

if (mysql_query(conn, "INSERT INTO routes(sender,destination,message_type,is_active ) VALUES((int)arrayValue[0],(char*)arrayValue[i]),..."))//Complete the VALUES(using array and typecast as per the data type in DB)
  {    
	finish_with_error(conn); 
  }
if(mysql_query(conn, "SELECT * FROM routes"))
{
	finish_with_error(conn);
}
MYSQL_RES *result = mysql_store_result(conn);
if (result == NULL)
{
	finish_with_error(conn);
}
int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  MYSQL_FIELD *field;
  
while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          if (i == 0) 
          {              
             while(field = mysql_fetch_field(result)) 
             {
                printf("%s ", field->name);
             }
             
             printf("\n");           
          }
          
          printf("%s  ", row[i] ? row[i] : "NULL"); 
      } 
  }
  
  printf("\n");
  
  mysql_free_result(result);
  mysql_close(conn);
//printf("connection success!\n\n");
return EXIT_SUCCESS;
}
