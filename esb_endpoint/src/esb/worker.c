// #include <stdio.h>
// #include <unistd.h>
// #include <bmd_parser.h>


// /**
//  * TODO: Implement the proper logic as per ESB specs.
//  */
// void *poll_database_for_new_requets(void *vargp)
// {
//     // Step 1: Open a DB connection
//     int i = 0;
//     while (i < 99)
//     {
//         i++;
        
//         printf("Sleeping for 5 seconds.\n");
//         sleep(5);
//     }
// }

#include <stdio.h>
#include <unistd.h>
#include "bmd_parser.h"
#include<mysql/mysql.h>
#include<string.h>
#include <pthread.h>

#define server "localhost"
#define user "root"
#define password "password"
#define database "esb_db"

char *get_name_dir(const char *s)
{
    char t = '/';
    const char *last = strrchr(s, t);
    if (last != NULL)
    {
        const size_t len = (size_t)(last - s);
        char *const n = malloc(len + 1);
        memcpy(n, s, len);
        n[len] = '\0';
        return strdup(n);
    }
    return NULL;
}

void dir_clean(char *path)
{ /* Deletes the BMD file specified by the path */
    
    remove(path);
    printf("Path is removed :%s\n", path);
    path = get_name_dir(path);
    /* Removes the directory created by random numberes*/
    rmdir(path);
    printf("Removed :%s\n", path);
    free(path);
}


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
/* Create a lock */
pthread_mutex_t lock;

typedef struct 
{
    const unsigned char* sender_id;
    const unsigned char* destination_id;
    const unsigned char* message_type;
     const unsigned char* location;
     const unsigned char* status;
    int id;
}tasktt;
int fetch_new_request_from_db(BMD *request,tasktt *task);
int fetch_new_request_from_db(BMD *request,tasktt *task)
{
    /** 
     * TODO: query the DB for this, and populate the 
     * request pointer with the requests.
     */
    //  printf("\nInside fetch_new_request\n");
    //  printf("%s %s",task->sender_id,request->bmd_envelope->Sender);
    //  printf("%s %s",task->destination_id,request->bmd_envelope->Destination);
    //  printf("%s %s",task->message_type,request->bmd_envelope->MessageType);
    //  printf("\nCompare request\n");

    if(task->sender_id ==(char*) request->bmd_envelope->Sender && 
        task->destination_id==(char*)request->bmd_envelope->Destination &&
        task->message_type==(char *)request->bmd_envelope->MessageType)
        {
            printf("Inside fetch_new_request and return 0\n");
            return 0;
        }

    printf("Checking for new requests in esb_requests table.\n");
    return 1; // 1 => OK, -1 => Errors
}

/**
 * TODO: Implement the proper logic as per ESB specs.
 */
void *poll_database_for_new_requets(void *vargp)
{


    
    // Step 1: Open a DB connection
    int i = 0;
    while (i>=0)
    {
       

        i++;


        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */

        MYSQL *con = mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;


        if (con == NULL) 
        {
            fprintf(stderr, "%s\n", mysql_error(con));
            return -1;
        }  
         //printf("hello");
        if (!mysql_real_connect(con, server, user, password, database, 0, NULL, 0)) 
        {
            printf("\n\nUser login problems\n\n");
            finish_with_error(con);
        }    
       // printf("hello");

        pthread_mutex_lock( & lock); 

        char *status="available";
            char query[5000];
        // printf("INSERT INTO esb_request(sender_id, dest_id, message_type, reference_id, message_id, received_on, status) VALUES ('%s','%s', '%s','%s', '%s','%s','%s'\n)", bmd->bmd_envelope->Sender, bmd->bmd_envelope->Destination, bmd->bmd_envelope->MessageType, bmd->bmd_envelope->ReferenceID, bmd->bmd_envelope->MessageID, received_on, status);
        
            sprintf(query, "SELECT sender_id, dest_id, message_type,data_location,id FROM esb_request WHERE status  = 'available'");  
        
        /*Query to insert values from BMD to DB*/
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }
        
    

        res = mysql_store_result(con);
        row = mysql_fetch_row(res);
        
        /**
         * Step 3:
         */


        tasktt task;

        if(row!=NULL)
        {
            /*
            char* sender=row[0];
            char* dest=row[1];
            char* msgType=row[2];
            char* locationBMD=row[3];

            printf("\n\n%s,%s,%s,%s\n\n",sender,dest,msgType,locationBMD);
            */
           task.sender_id=(char*)(row[0]);
           task.destination_id=row[1];
           task.message_type=row[2];
           task.location=row[3];
            task.id=atoi(row[4]);
            task.status=status;
          //  printf("\n%s",task.sender_id);
            printf("\n\ntask_id:%d row_id:%s\n\n",task.id,row[4]);
           printf("\n\n%s,%s,%s,%s\n\n",task.destination_id,task.location,task.message_type,task.sender_id);

            BMD *bmd = (BMD *)(malloc(sizeof(BMD *)));
            printf("$%s$",task.location);
           bmd=processXML(task.location);
          //  printf("\n\nBMD values:%s %s",bmd->bmd_envelope->Sender,bmd->bmd_envelope->Destination);


           //  printf("\nInside fetch_new_request\n");
            // printf("%s %s",task.sender_id,bmd->bmd_envelope->Sender);
            // printf("%s %s",task.destination_id,bmd->bmd_envelope->Destination);
            // printf("%s %s",task.message_type,bmd->bmd_envelope->MessageType);
            // printf("\nCompare request\n");
            if(strcmp(task.sender_id,bmd->bmd_envelope->Sender)==0
            && strcmp(task.destination_id,bmd->bmd_envelope->Destination)==0 
            && strcmp(task.message_type,bmd->bmd_envelope->MessageType)==0)
            {
                /**
                 * found a row in esb_request
                 * that has status "available"
                 * change status to "taken"
                 * and if completed set status to "done" 
                */
                printf("Inside fetch_new_request and return 0 and id:%d\n",task.id);
                task.status="taken";

                if(change_available_to_taken(task.id,task.status)==1)
                {
                    printf("\nUpdated\n");

                }
                else
                {
                    printf("FAILED:");
                    task.status="available";
                    change_available_to_taken(task.id,task.status);
                    
                }
                
            
            /**
              * Found a new request, so we will now process it.
              * See the ESB specs to find out what needs to be done
              * in this step. Basically, you will be doing:
              * 1. Find if there is any transformation to be applied to
              *    the payload before transporting it to destination.
              * 2. If needed, transform the request.
              * 3. Transport the transformed data to destination.
              * 4. Update the status of the request in esb_requests table
              *    to mark it as done (or error) depending on the outcomes
              *    of this step.
              * 5. Cleanup
              */
                printf("Applying transformation and transporting steps.\n");
                if(ttfunc(bmd)==0)
                {
                    task.status="done";
                    change_available_to_taken(task.id,task.status);
                    freebmd(bmd);
                    printf("\n");
                    printf("...........................BMD FREE..................................................\n");
                     dir_clean(task.location);
                      printf("\n");
                     printf("...........................Cleaning Directory..................................................");
                    printf("\n\n...........................Completed:Endpoint..................................\n\n");
                }

            }
            else
            {
                /* code */
                printf("fetch_new_request_from_db(&bmd,&task)==0:FAILED\n");
                pthread_mutex_unlock( & lock);
            break;
            }
            
        /* free results */
       
        }

         mysql_free_result(res);

        // if (fetch_new_request_from_db(&req))
        // {
        //     /**
        //       * Found a new request, so we will now process it.
        //       * See the ESB specs to find out what needs to be done
        //       * in this step. Basically, you will be doing:
        //       * 1. Find if there is any transformation to be applied to
        //       *    the payload before transporting it to destination.
        //       * 2. If needed, transform the request.
        //       * 3. Transport the transformed data to destination.
        //       * 4. Update the status of the request in esb_requests table
        //       *    to mark it as done (or error) depending on the outcomes
        //       *    of this step.
        //       * 5. Cleanup
        //       */
        //     printf("This is number:%d\n",i);
        //     printf("Applying transformation and transporting steps.\n");
        // }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
   
        printf("Sleeping for 5 seconds.\n");
         pthread_mutex_unlock( & lock);
         sleep(5);
    }
     
            // pthread_mutex_unlock( & lock);
           
    printf("while loop...............................................\n");
}
