
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

    void update_esb_request(char *status,int id)
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
    sprintf(query,"update esb_request set status= '%s' where id = '%d' ",status,id);
    

    if(mysql_query(con,query)){
     finish_with_error(con);
    }
    
    sprintf(query,"select * from esb_request where id = '%d' ",id);
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
      printf("no such id present");
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
   char *status = "r2";
   int id = 1;
   update_esb_request(status,id);
   return 0;
}
