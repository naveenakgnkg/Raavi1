//gcc insert.c -o insert -std=c99  `mysql_config --cflags --libs`

#include <stdio.h>
#include<stdlib.h>
#include <mysql.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int main(int argc, char **argv)
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
  
  if (mysql_query(con, "DROP TABLE IF EXISTS esb_request")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE Cars(Id INT,sender_id VARCHAR(45),dest_id VARCHAR(45),message_type VARCHAR(45),reference_id VARCHAR(45),message_id VARCHAR(45),recevied_on DATETIME,data_location TEXT,status VARCHAR(20),status_details TEXT)")) 
  {      
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES()")) {
      finish_with_error(con);
  }

  mysql_close(con);
  exit(0);
}
