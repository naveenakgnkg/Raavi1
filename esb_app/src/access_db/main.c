#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* Contains necessary C functions of mysql */
#include <mysql.h>
#include "head.h"

int main()
{
char *sender_id,*destination_id,*message_type,*reference_id,*message_id,*data_location,*status,*status_details,*is_active;
sender_id="f47"; destination_id = "f48"; message_type = "Credit"; is_active = "1";
reference_id="r3"; message_id="r4"; data_location="xyz"; status="r3"; status_details="xyz";
//connection_to_db();

connection_to_db2(4);
//printf("%d",c2);
//insert_to_routes(&sender_id,&destination_id,&message_type,&is_active);
esb_request (&sender_id,&destination_id,&message_type,&reference_id,&message_id,&data_location,&status,&status_details);
return EXIT_SUCCESS;
}
