#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <bmd_parser.h>
#include <mysql.h>
#include <../database/database.h>

#define server "localhost"
#define user "root"
#define password "password"
#define database "esb_db"

int validate_xml_file( BMD * bmd_file,char* bmdfileloc)
{
  if(validBmdXml(bmd_file)==0)
  {
     
	  int route_val=activeRouteCheck(bmd_file->bmd_envelope->Sender,bmd_file->bmd_envelope->Destination,bmd_file->bmd_envelope->MessageType);
      if(route_val ==-1)
      {
        printf("Route_id Validation:FAILED\n");
        return -1;
      }
      else
      {
        int route_id=routeId(bmd_file->bmd_envelope->Sender,bmd_file->bmd_envelope->Destination,bmd_file->bmd_envelope->MessageType);
        printf("route_id:%d for bmd->sender:%s\n",route_id,bmd_file->bmd_envelope->Sender);
        if(transportConfigCheck(route_id)==0)
        {
          if(transformConfigCheck(route_id)==0)
          {
            printf("Validation:SUCCESS\n");
		 	if(sqlcon(bmd_file,bmdfileloc)==0)
			{
				printf("Success: added to DB\n");
				return 0;
			}
			else
			{
				printf("Load BMD data to DB: FAILED\n");
			}
            
          }
          else
          {
            printf("transform Validation:FAILED\n");
            return -1;
          }
          
        }
        else
          {
            printf("transport Validation:FAILED\n");
            return -1;
          }
      }
      
      
      
  }
  else
  {
    printf("BMD validation:FAILED\n");
    return -1;
  }
  
}



int validBmdXml( BMD * bmd_file)
{
  /* MessageID */
  if(strcmp(bmd_file->bmd_envelope->MessageID ,"" )==0) {
    fprintf(stderr,"Message ID doesnot exist in bmd");
    return 1;
  }

  /* MessageType */
  if(strcmp(bmd_file->bmd_envelope->MessageType ,"") ==0){
    fprintf(stderr,"Message Type doesnot exist in bmd");
    return 1;
  }

  /* Sender */
  if(strcmp(bmd_file->bmd_envelope->Sender,"")==0) {
    fprintf(stderr,"Sender doesnot exist in bmd\n");
    return 1;
  }


  /* Destination */
  if(strcmp(bmd_file->bmd_envelope->Destination ,"")==0 ){
    fprintf(stderr,"Destination doesnot exist in bmd");
    return 1;
  }


  /* CreationDateTime */
  if(strcmp(bmd_file->bmd_envelope->CreationDateTime ,"")==0) {
    fprintf(stderr,"CreationDateTime doesnot exist in bmd");
    return 1;
  }


  /* Signature */
  if(strcmp(bmd_file->bmd_envelope->Signature ,"")==0) {
    fprintf(stderr,"Signature doesnot exist in bmd");
    return 1;
  }

  /* ReferenceID */
  if(strcmp(bmd_file->bmd_envelope->ReferenceID , "")==0 ){
      fprintf(stderr,"ReferenceID doesnot exist in bmd");
      return 1;
  }

  /* payload */
  if(strcmp(bmd_file->bmd_payload->data , "")==0) {
    fprintf(stderr,"Payload doesnot exist in bmd");
    return 1;
   }
  return 0;
}

int activeRouteCheck(const unsigned char *Sender, const unsigned char *Destination,const unsigned char *MessageType)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Execute SQL query to fetch all table names.*/
	sprintf(query,"SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'  AND is_active=b'1'", Sender, Destination, MessageType);
	
	if (mysql_query(conn, query))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);
	if ((row = mysql_fetch_row(res)) != NULL)
	{
			success = atoi(row[0]);
	}
	else
	{
		success = -1;
	}

	mysql_free_result(res);
	return success;
}

int transportConfigCheck(int route_id)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Execute SQL query to fetch all table names.*/
	sprintf(query, "SELECT * FROM transport_config WHERE route_id='%d'",route_id);
	//printf("%s",query);
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}
    
	res = mysql_use_result(conn);

	if (res->field_count >= 1)
	{
		success=0;
	}
	else
	{
		success = -1;
	}

	/* free results */
	mysql_free_result(res);
	return success;
}

int transformConfigCheck(int route_id)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	
	sprintf(query, "SELECT * FROM transform_config WHERE route_id=%d",route_id);
	
	//printf("%s",query);
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}
    
	res = mysql_use_result(conn);

	if (res->field_count >= 1)
	{
		success=0;
	}
	else
	{
		success = -1;
	}

	/* free results */
	mysql_free_result(res);
	return success;
}

/* for testing:
int main()
{
    char  filepath[50];
    scanf("%s",filepath);
    bmd  * bd = (bmd*) malloc (sizeof(bmd));
    validate_xml_file(bd)? printf("1"): printf("2");
    printf("\n");
    return 0;
}
*/
