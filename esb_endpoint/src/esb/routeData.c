#include<mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../esb/db_header.h"
#define server "localhost"
#define user "root"
#define password "password"
#define database "esb_db"


int routeId(const unsigned char* sender,const unsigned char* destination,const unsigned char* msgtype)
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
	}

	
	sprintf(query,"SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'", sender,destination,msgtype);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
    int route_id = atoi(row[0]);

	/* free results */
	mysql_free_result(res);
	return route_id;
}

char* transformKey(int route_id)
{

    char* transformKey;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/*Get transform config_value*/
	sprintf(query, "SELECT config_key FROM transform_config WHERE route_id='%d'", route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	strcpy(transformKey,strdup(row[0]));
	//printf("transformKey:%s\n",key);
	/* free results */
	mysql_free_result(res);
	return strdup(transformKey);
}

char* transportKey(int route_id)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
    char* transport_key;
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Get transform config_key */ 
	sprintf(query, "SELECT config_key FROM transport_config WHERE route_id='%d'", route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	strcpy(transport_key,row[0]);
	
	/* free results */
	mysql_free_result(res);
	printf("transport_key:%s\n",transport_key);
	return strdup(transport_key);
}

char* transportValue(int route_id)
{
    char* transport_value;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/*Get transform config_value*/
	sprintf(query, "SELECT config_value FROM transport_config WHERE route_id='%d'", route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	strcpy(transport_value,strdup(row[0]));

	/* free results */
	mysql_free_result(res);
	printf("transport_value:%s\n",transport_value);
	return transport_value;
}

char* transformValue(int route_id)
{
    char* transform_value;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/*Get transform config_value*/
	sprintf(query, "SELECT config_value FROM transform_config WHERE route_id='%d'", route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	strcpy(transform_value,strdup(row[0]));

	/* free results */
	mysql_free_result(res);
	
	printf("transform_value:%s\n",transform_value);

	return transform_value;
}
