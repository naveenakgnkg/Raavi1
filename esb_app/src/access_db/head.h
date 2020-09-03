#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include "connection.c"
#include "connection2.c"
#include "routes.c"
#include "esb_request3.c"

void connection_to_db();
void insert_to_routes(char **sender,char **destination,char **message_type,char **is_active);
int connection_to_db2(int x);
void esb_request ( char **sender_id, char **dest_id, char **message_type,char **reference_id, char **message_id,char **data_location,char **status,char **status_details);

#endif
