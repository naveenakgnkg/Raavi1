// #include <mysql.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include "../esb/bmd_parser.h"

// #define server "localhost"
// #define user "root"
// #define password "password"
// #define database "esb_db"


// /*

// int check_new_request(int id)
// {
// 	int success = 0;

// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
// 	conn = mysql_init(NULL);

	
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

	
// 	sprintf(query, "SELECT * FROM esb_request WHERE status = 'available' AND id='%d' LIMIT 1", id);
	
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);
//         int retval = mysql_num_rows(res);
// 	printf("\nrows:\t%d\n",retval);
// 	if (retval >0)
// 	{
// 		success=0;
// 	}
// 	else
// 	{
// 		success =-1;
// 	}

	
// 	mysql_free_result(res);
// 	return success;
// }

// void change_available_to_taken(int id)
// {

// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
// 	conn = mysql_init(NULL);

	
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

	
// 	sprintf(query, "UPDATE esb_request SET status = 'taken'  WHERE id='%d'", id);
	
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);

	
// 	mysql_free_result(res);
// }

// void change_taken_to_done(int id)
// {

// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
// 	conn = mysql_init(NULL);

// 	/* Connect to database 
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

	
// 	sprintf(query, "UPDATE esb_request SET status = 'done'  WHERE id='%d'", id);
// 	/* Execute SQL query.
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);

// 	/* free results 
// 	mysql_free_result(res);
// }
// */
// int routeId(char* sender, char* destination, char* msgtype)
// {

// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
// 	conn = mysql_init(NULL);

// 	/* Connect to database */
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

	
// 	sprintf(query,"SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'", sender,destination,msgtype);
// 	/* Execute SQL query.*/
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);
// 	row = mysql_fetch_row(res);
	
//     int route_id = atoi(row[0]);

// 	/* free results */
// 	mysql_free_result(res);
// 	return route_id;
// }

// char* transformKey(int route_id)
// {

//     char* key;
// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
// 	conn = mysql_init(NULL);

// 	/* Connect to database */
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

// 	/*Get transform config_value*/
// 	sprintf(query, "SELECT config_key FROM transform_config WHERE route_id='%d'", route_id);
// 	/* Execute SQL query.*/
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);
// 	row = mysql_fetch_row(res);
	
// 	strcpy(key,strdup(row[0]));

// 	/* free results */
// 	mysql_free_result(res);
// 	return key;
// }

// void add_payload(char Payload_value[], int route_id, char* transport_key)
// {
// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
// 	conn = mysql_init(NULL);
	
// 	/* Connect to database */
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

// 	/* Get transform config_key */ 
// 	sprintf(query, GET_transportkey, route_id);
// 	/* Execute SQL query.*/
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);
// 	row = mysql_fetch_row(res);
	
// 	strcpy(transport_key,row[0]);
	
// 	for(int i=0;i<strlen(Payload_value);i++)
// 	{
// 		char ch = Payload_value[i];
// 		strncat(transport_key, &ch, 1);
// 	}
	
// 	/* free results */
// 	mysql_free_result(res);
	
// }

// char* transportKey(int route_id)
// {
// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
//     char* transport_key;
// 	conn = mysql_init(NULL);
	
// 	/* Connect to database */
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

// 	/* Get transform config_key */ 
// 	sprintf(query, "SELECT config_key FROM transport_config WHERE route_id='%d'", route_id);
// 	/* Execute SQL query.*/
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);
// 	row = mysql_fetch_row(res);
	
// 	strcpy(transport_key,row[0]);
	
// 	/* free results */
// 	mysql_free_result(res);
// 	return transport_key;
// }

// char* transportValue(int route_id)
// {
//     char* transport_value;
// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
// 	conn = mysql_init(NULL);

// 	/* Connect to database */
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

// 	/*Get transform config_value*/
// 	sprintf(query, "SELECT config_value FROM transport_config WHERE route_id='%d'", route_id);
// 	/* Execute SQL query.*/
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);
// 	row = mysql_fetch_row(res);
	
// 	strcpy(transport_value,strdup(row[0]));

// 	/* free results */
// 	mysql_free_result(res);
// 	return transport_value;
// }



// char* transformValue(int route_id)
// {
//     char* transform_value;
// 	MYSQL *conn;
// 	MYSQL_RES *res;
// 	MYSQL_ROW row;
// 	char query[5000];
// 	conn = mysql_init(NULL);

// 	/* Connect to database */
// 	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
// 	{
// 		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
// 	}

// 	/*Get transform config_value*/
// 	sprintf(query, "SELECT config_value FROM transform_config WHERE route_id='%d'", route_id);
// 	/* Execute SQL query.*/
// 	if (mysql_query(conn, query))
// 	{
// 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	}

// 	res = mysql_store_result(conn);
// 	row = mysql_fetch_row(res);
	
// 	strcpy(transform_value,strdup(row[0]));

// 	/* free results */
// 	mysql_free_result(res);
// 	return transform_value;
// }