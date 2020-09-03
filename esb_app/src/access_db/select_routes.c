
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
void finish_with_error(MYSQL *conn)
{
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(conn),mysql_errno(conn));
	mysql_close(conn);
	exit(1);
}

    void select_routes(char *message_type,char *sender)
    {
    MYSQL *con;
    con = mysql_init(NULL);
    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "esb_db";


    con = mysql_init(NULL);
    if(! mysql_real_connect(con, server, user, password,database,0,NULL,0))
    {
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(con),mysql_errno(con));
	exit(1);
    }
    printf("Connection Successful!\n\n");

    char query[500];
    sprintf(query,"select * from routes where message_type = '%s' and sender = '%s' and is_active = 1 ",message_type,sender);

    if(mysql_query(con,query)){
     finish_with_error(con);
    }
    MYSQL_RES *result;
    result = mysql_store_result(con);
    if(result==NULL)
    {
      finish_with_error(con);
    }

     /* shows number of fields*/ 
    int num_fields = mysql_num_fields(result);


    MYSQL_ROW row;

 // it holds field value
    MYSQL_FIELD *field;

      while(field = mysql_fetch_field(result)) {
       printf(" %s ",field->name);
    } 
      printf("\n");
      int n = mysql_num_rows(result);
      if(n==0)
      {
      printf("not matching with input data");
      return;
      }
      else{
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
                    }
        printf("\n");
    }
    }
    mysql_free_result(result);
    mysql_close(con);
    }

int main()
{
   char *sender = "abc1";
   char *message_type = "creaditReport";
   select_routes(message_type,sender);
   return 0;
}
