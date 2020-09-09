/*sample values
*INSERT INTO transform_config(route_id,config_key,config_value) VALUES(101,'VARCHAR101','EGTEXT');
*/


#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <bmd_parser.h>

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
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, "localhost", "root", "password", 
          "transform_config", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  
  if (mysql_query(con, "SELECT * FROM transform_config")) 
  {
      finish_with_error(con);
  }
  
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) 
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
  
  mysql_free_result(result);
  mysql_close(con);
  
  exit(0);
}










// //gcc insert.c -o insert -std=c99  `mysql_config --cflags --libs`

// #include <mysql.h>
// #include <stdio.h>
// #include <string.h>
// #include <bmd_parser.h>

// void finish_with_error(MYSQL *con)
// {
//   fprintf(stderr, "%s\n", mysql_error(con));
//   mysql_close(con);
//   exit(1);        
// }
// /*function call to sqlcon:
// *converts to datetime format
// *insert data to database
// *fixed ID as auto increment
// */
// void sqlcon(BMD *bmd)
// {
//   MYSQL *con = mysql_init(NULL);
//    int8_t received_temp[100]; //= "2020-08-12T05:18:00+0000";
//    strncpy(received_temp,bmd->bmd_envelope->CreationDateTime,19);
//   int n = strlen(received_temp);
//   int8_t received_on[100];
//   	for(int i=0;i<=n; i++)//removing +0000;
//   	{
//   		received_on[i] = received_temp[i];
//   		if(received_on[i]=='T')		//test for character
// 		{
// 			received_on[i] = ' '; // write next character back to current position
// 		}

//       }
//  if (con == NULL) 
//   {
//       fprintf(stderr, "%s\n", mysql_error(con));
//       exit(1);
//   }  

//   if (mysql_real_connect(con, "localhost", "sammy", "password", 
//           "esb_db", 0, NULL, 0) == NULL) 
//   {
//       printf("\n\nUser login problem\n\n");
//       finish_with_error(con);
//   }    

//   char *status="availble";
// 	char query[5000];
//  // printf("INSERT INTO esb_request(sender_id, dest_id, message_type, reference_id, message_id, received_on, status) VALUES ('%s','%s', '%s','%s', '%s','%s','%s'\n)", bmd->bmd_envelope->Sender, bmd->bmd_envelope->Destination, bmd->bmd_envelope->MessageType, bmd->bmd_envelope->ReferenceID, bmd->bmd_envelope->MessageID, received_on, status);
   
// 	 sprintf(query, "INSERT INTO esb_request(sender_id, dest_id, message_type, reference_id, message_id, received_on, status) VALUES ('%s','%s', '%s','%s', '%s','%s','%s')", bmd->bmd_envelope->Sender, bmd->bmd_envelope->Destination, bmd->bmd_envelope->MessageType, bmd->bmd_envelope->ReferenceID, bmd->bmd_envelope->MessageID, received_on, status);  
 
//  /*Query to insert values from BMD to DB*/
//   if (mysql_query(con, query)) {
//       finish_with_error(con);
//   }
//   printf("\nSuccess bmd parsed to DB\n");
  
//   mysql_close(con);
//   exit(0);
// }
