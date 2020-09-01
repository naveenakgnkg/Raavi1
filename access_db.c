#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

void finish_with_error(MYSQL *conn)
{
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(conn),mysql_errno(conn));
	mysql_close(conn);
	exit(1);
}

int main()
{
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
if (mysql_query(conn, "INSERT INTO routes(sender,destination,message_type,is_active ) VALUES('ab1','yz1','credit',1)"))
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
