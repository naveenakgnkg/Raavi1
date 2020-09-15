#ifndef TRANSFORM_H
#define TRANSFORM_H


char* payloadToJson(BMD*);
char* payloadToXml(BMD*);
int decision(BMD* bmd,char* transformvalue,char* transformkey,char* transportvalue,char* transportkey);
#endif