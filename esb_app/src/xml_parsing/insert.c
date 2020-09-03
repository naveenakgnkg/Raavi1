//gcc insert.c -o insert -std=c99  `mysql_config --cflags --libs`

#include <stdio.h>
#include<stdlib.h>
#include <mysql.h>
#include<string.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int insertDB(char** array)
{
  MYSQL *con = mysql_init(NULL);
  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", "sammy", "password", 
          "bmd", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  //if table exists don't create table again
  if (mysql_query(con, "DROP TABLE IF EXISTS esb_request")) {
      finish_with_error(con);
  }
  //creating esb_request table
  if (mysql_query(con, "CREATE TABLE esb_request(Id INT,sender_id VARCHAR(45),
  dest_id VARCHAR(45),message_type VARCHAR(45),reference_id VARCHAR(45),
  message_id VARCHAR(45),recevied_on TEXT,data_location TEXT,status VARCHAR(20),status_details TEXT)")) 
  {      
      finish_with_error(con);
  }
  //adding values to table
  //temperory array -> values from bmd array
  char* array[]={
      "1","'sender_id'","'dest_id'","message_type","'reference_id'",
      "'message_id'","'1010-12-01 23:59:59'","'data_location'","'status'","'status_details'"
  };

  //concat string for query
 char dest[1000]="INSERT INTO esb_request VALUES(";
 for(int i=0;i<10;i++)
 {
    char* src=*(array+i);
    strcat(dest, src);
    if(i<9)
    strcat(dest,",");
    //printf("%s\n",dest);
 }
    strcat(dest,")");
   
//adding values to the database
//INSERT INTO esb_request VALUES()
  if (mysql_query(con,dest)) {
      finish_with_error(con);
  }
  //SUCCESS Inserted values in table
  printf("Insert success\n");
  mysql_close(con);
  exit(0);
}
