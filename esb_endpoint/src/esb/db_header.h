#include<stdio.h>
#include<stdlib.h>

char* transformKey(int route_id);
int routeId(const unsigned char* sender,const unsigned char* destination,const unsigned char* msgtype);
int sendMail(char *to, char *text);
char* transportKey(int route_id);
char* transportValue(int route_id);
char* transformValue(int route_id);
int transformConfigCheck(int id);
int transportConfigCheck(int id);
int activeRouteCheck(const unsigned char* sender,const unsigned char* destination,const unsigned char* msgtype);
