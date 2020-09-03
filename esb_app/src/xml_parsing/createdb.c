#include <stdio.h>
#include<stdlib.h>
#include <mysql.h>
#include"function.h"

int readXml(char* name)
{  
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }
  //accessing database through id and password
  if (mysql_real_connect(con, "localhost", "root", "password", 
          NULL, 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }  
  //concat command for creating database;
  char* pass="CREATE DATABASE ";
  strcat(pass,name); 

  if (mysql_query(con,pass)) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  mysql_close(con);
  exit(0);
}
