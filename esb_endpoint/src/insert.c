//gcc insert.c -o insert -std=c99  `mysql_config --cflags --libs`

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
/*function call to sqlcon:
*converts to datetime format
*insert data to database
*fixed ID as auto increment
*/
int sqlcon(BMD *bmd,char *bmdfileloc)
{
  MYSQL *con = mysql_init(NULL);
  //  int8_t received_temp[100]; //= "2020-08-12T05:18:00+0000";
  //  strncpy(received_temp,bmd->bmd_envelope->CreationDateTime,19);
  // int n = strlen(received_temp);
  // int8_t received_on[20];
  // 	for(int i=0;i<=16; i++)//removing +0000;
  // 	{
  // 		received_on[i] = received_temp[i];
  // 		if(received_on[i]=='T')		//test for character
	// 	{
	// 		received_on[i] = ' '; // write next character back to current position
	// 	}

  //     }

   int8_t received_temp[100]="0"; //= "2020-08-12T05:18:00+0000";
   strncpy(received_temp,bmd->bmd_envelope->CreationDateTime,19);
  int n = strlen(received_temp);
  int8_t received_on[100]="0";
  	for(int i=0;i<=n; i++)//removing +0000;
  	{
  		received_on[i] = received_temp[i];
  		if(received_on[i]=='T')		//test for character
		{
			received_on[i] = ' '; // write next character back to current position
		}

      }




 if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      return -1;
  }  

  if (mysql_real_connect(con, "localhost", "sammy", "password", 
          "esb_db", 0, NULL, 0) == NULL) 
  {
      printf("\n\nUser login problem\n\n");
      finish_with_error(con);
  }    

  char *status="available";
	char query[5000];
 // printf("INSERT INTO esb_request(sender_id, dest_id, message_type, reference_id, message_id, received_on, status) VALUES ('%s','%s', '%s','%s', '%s','%s','%s'\n)", bmd->bmd_envelope->Sender, bmd->bmd_envelope->Destination, bmd->bmd_envelope->MessageType, bmd->bmd_envelope->ReferenceID, bmd->bmd_envelope->MessageID, received_on, status);
   
	 sprintf(query, "INSERT INTO esb_request(sender_id, dest_id, message_type, reference_id, message_id, received_on, status,data_location) VALUES ('%s','%s', '%s','%s', '%s','%s','%s','%s')", bmd->bmd_envelope->Sender, bmd->bmd_envelope->Destination, bmd->bmd_envelope->MessageType, bmd->bmd_envelope->ReferenceID, bmd->bmd_envelope->MessageID, received_on, status,bmdfileloc);  
 
 /*Query to insert values from BMD to DB*/
  if (mysql_query(con, query)) {
      finish_with_error(con);
  }
  printf("\nSuccess bmd parsed to DB\n");
  
  mysql_close(con);
  return 0;
}

/*test code:(for debug purpose)


//gcc insert.c -o insert -std=c99  `mysql_config --cflags --libs`

#include <mysql.h>
#include <stdio.h>
#include <string.h>


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int main()
{
  MYSQL *con = mysql_init(NULL);
  printf("\n\nIn sqlcon function\n\n");
//   int8_t received_temp[100]; //= "2020-08-12T05:18:00+0000";
//   int8_t received_on[100];
//   strcpy(received_temp,bmd->bmd_envelope->CreationDateTime);


// int n = strlen(received_temp);
//   	for(int i=0;i<n-5; i++)//removing +0000;
//   	{
//   		received_on[i] = received_temp[i];
//   		if(received_on[i]=='T')		//test for character
// 		{
// 			received_on[i] = ' '; // write next character back to current position
// 		}

//       }

// printf("\n\nDateFormated %s\n\n",received_on);






  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", "sammy", "password", 
          "bmd", 0, NULL, 0) == NULL) 
  {
      printf("\n\nUser login problem\n\n");
      finish_with_error(con);
  }    
  
//   if (mysql_query(con, "DROP TABLE IF EXISTS esb_request")) {
//       finish_with_error(con);
//   }
  
//   if (mysql_query(con, "CREATE TABLE Cars(Id INT,sender_id VARCHAR(45),dest_id VARCHAR(45),message_type VARCHAR(45),reference_id VARCHAR(45),message_id VARCHAR(45),recevied_on DATETIME,data_location TEXT,status VARCHAR(20),status_details TEXT)")) 
//   {      
//       finish_with_error(con);
//   }
    /*int8_t ID = 5;
    char *status="availble";
	char query[5000];
     printf("INSERT INTO esb_request(sender_id, dest_id, message_type, reference_id, message_id, received_on,status) VALUES (%s,%s,%s,%s,%s,%s,%s)\n\n", bmd->bmd_envelope->Sender ,bmd->bmd_envelope->Destination,bmd->bmd_envelope->MessageType,bmd->bmd_envelope->ReferenceID,bmd->bmd_envelope->MessageID,bmd->bmd_envelope->CreationDateTime,status);
     
	 sprintf(query, "INSERT INTO esb_request(id, sender_id, dest_id, message_type, reference_id, message_id, received_on, status) VALUES (%d, '%s','%s', '%s','%s', '%s','%s','%s')", ID, bmd->bmd_envelope->Sender, bmd->bmd_envelope->Destination, bmd->bmd_envelope->MessageType, bmd->bmd_envelope->ReferenceID, bmd->bmd_envelope->MessageID, received_on, status);
	 
    if (mysql_query(con, "USE esb_db;")) {
      finish_with_error(con);
  } 

CREATE TABLE temp (
    id INT,
    name VARCHAR(25)
);



	int id=50;
	char* name="Suyash";
  	char query[5000];
	sprintf(query, "INSERT INTO temp(id,name) VALUES(%d,'%s')",id,name);
  if (mysql_query(con, query)) {
      finish_with_error(con);
  }

  mysql_close(con);
  exit(0);
}
*/