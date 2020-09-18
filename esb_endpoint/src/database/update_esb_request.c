#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* Contains necessary C functions of mysql */
#include <mysql.h>

#define STRING_SIZE 100

// void finish_with_error(MYSQL *con) {

//   fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
//   mysql_close(con);

//   exit(1);        
// }


#define server "localhost"
#define user "root"
#define password "password"
#define database "esb_db"



//#define AVAILABLE_TO_TAKEN "UPDATE esb_request SET status = 'taken'  WHERE id='%d'"  
#define TAKEN_Q "UPDATE esb_request SET status = '%s' WHERE id = '%d' " 
int change_available_to_taken(int id,char* status)
{

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
		return 0;
	}

	
	sprintf(query,TAKEN_Q ,status,id);
	//sprintf(query, "UPDATE esb_request SET status = 'done' WHERE id = '%d' ",id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
		return 0;
	}

	res = mysql_store_result(conn);

	/* free results */
	mysql_free_result(res);

  return 1;
}


/*testing with a sample input*/
// int main() {
  
//  change_available_to_taken(1);
//  return 0;
// }
