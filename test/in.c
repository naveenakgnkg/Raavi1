//gcc insert.c -o insert -std=c99  `mysql_config --cflags --libs`

#include <stdio.h>
#include<stdlib.h>
#include <mysql.h>
#include"function.h"
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int newValue(char* value)
{
  MYSQL *con = mysql_init(NULL);
  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", "sammy", "password", 
          "esb", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  
  if (mysql_query(con, "DROP TABLE IF EXISTS Cars")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE Cars(Id INT,Name TEXT, Price INT)")) 
  {      
      finish_with_error(con);
  }
  
  if (mysql_query(con,value)) {
      finish_with_error(con);
  }

  mysql_close(con);
  exit(0);

return 0;
}
