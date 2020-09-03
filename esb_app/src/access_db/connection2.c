int connection_to_db2(int x)
{
 MYSQL *con ;  /*database connection handle*/

  con = mysql_init(NULL);


  if (con == NULL) {

      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */


char *server = "localhost";
char *user = "root";
char *password = "root";
char *database = "esb_db";


if(! mysql_real_connect(con, server, user, password,database,0,NULL,0))
{
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(con),mysql_errno(con));
	exit(1);
} 



  
  
  mysql_close(con);
printf("connection success!\n\n");
}
