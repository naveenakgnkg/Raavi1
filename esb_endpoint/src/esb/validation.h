#ifndef VALIDATION 
#define VALIDATION 
#include<bmd_parser.h>

int validate_xml_file( BMD *);
int activeRouteCheck(const unsigned char *, const unsigned char *, const unsigned char *);
int transportConfigCheck(int );
int transformConfigCheck(int );

#endif