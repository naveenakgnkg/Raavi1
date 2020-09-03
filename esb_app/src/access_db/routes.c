

void insert_to_routes(char **sender,
char **destination,char **message_type,char **is_active) {
#define STRING_SIZE 100


#define INSERT_QUERY "INSERT INTO                            \
routes(route_id,sender,destination,message_type,is_active)    \
VALUES(?,?,?,?,1)"
void finish_with_error(MYSQL *conn)
{
	fprintf(stderr, "\nError: %s [%d]\n",mysql_error(conn),mysql_errno(conn));
	mysql_close(conn);
	exit(1);
}


MYSQL_STMT    *stmt;
MYSQL_BIND    bind[4];
my_ulonglong  affected_rows;
int           param_count;
int           id; 
char          sender_data[STRING_SIZE];
char          destination_data[STRING_SIZE];
char          message_type_data[STRING_SIZE];
unsigned long str_length[3];
bool          is_null;

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
/* Prepare an INSERT query with 3 parameters */
stmt = mysql_stmt_init(con);
if (!stmt) {
  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
  exit(0);
}

if (mysql_stmt_prepare(stmt, INSERT_QUERY, strlen(INSERT_QUERY))) {
  fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}
fprintf(stdout, " prepare, INSERT successful\n");

/* Get the parameter count from the statement */
param_count= mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in INSERT in routes: %d\n", param_count);

/* validate parameter count */
if (param_count != 4) {
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
}

/* Bind the data for all 3 parameters */
memset(bind, 0, sizeof(bind));

/* This is a number type, so there is no need to specify buffer_length */
/* INTEGER PARAM */
bind[0].buffer_type= MYSQL_TYPE_LONG;
bind[0].buffer= (char *)&id;
bind[0].is_null= 0;
bind[0].length= 0;

/* STRING PARAM */
bind[1].buffer_type= MYSQL_TYPE_STRING;
bind[1].buffer= (char *)&sender_data;
bind[1].is_null= 0;
bind[1].length= &str_length[0];
bind[1].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[2].buffer_type= MYSQL_TYPE_STRING;
bind[2].buffer= (char *)destination_data;
bind[2].buffer_length= STRING_SIZE;
bind[2].is_null= 0;
bind[2].length= &str_length[1];

/* STRING PARAM */
bind[3].buffer_type= MYSQL_TYPE_STRING;
bind[3].buffer= (char *)&message_type_data;
bind[3].is_null= 0;
bind[3].buffer_length= STRING_SIZE;
bind[3].length= &str_length[2];

/* Bind the buffers */
if (mysql_stmt_bind_param(stmt, bind)) {
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

if (mysql_query(con, "SELECT * FROM routes")) {
      finish_with_error(con);
}
  
MYSQL_RES *result = mysql_store_result(con);
  
if (result == NULL) {
      finish_with_error(con);
}
  
int row_id;
MYSQL_ROW row;
while ((row = mysql_fetch_row(result))) {               
         row_id = atoi(row[0]);
}

  mysql_free_result(result);
row_id+=1;
id=row_id;
strncpy(sender_data,*sender, STRING_SIZE);
strncpy(destination_data,*destination, STRING_SIZE);
str_length[0]= strlen(sender_data);
str_length[1]=strlen(destination_data);
strncpy(message_type_data,*message_type,STRING_SIZE);        /* smallint */
str_length[2]=strlen(message_type_data);
//is_null= 0;               /* reset */

/* Execute the INSERT statement - 2*/
if (mysql_stmt_execute(stmt)) {
  fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

/* Get the total rows affected */
affected_rows= mysql_stmt_affected_rows(stmt);
fprintf(stdout, " total affected rows in routes: %lu\n",
                (unsigned long) affected_rows);

/* validate affected rows */ 
if (affected_rows != 1) {
  fprintf(stderr, " invalid affected rows by MySQL\n");
  exit(0);
}

/* Close the statement */
if (mysql_stmt_close(stmt)) {
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
} printf("connection id: %ld\n", mysql_thread_id(con));

  mysql_close(con);
}


