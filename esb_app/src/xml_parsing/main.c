#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"function.h"

int main()
{
	//passing xml file name
	char* name="bmd.xml";
	if(readXml(name))
	{
		printf("Reading XML data success\n");
	}
	else
	{
		printf("XML parsing failed");
		exit(0);
	}
	//adding array data to database
	char* database="esb_db";
	//char* val="INSERT INTO Cars VALUES(100,'AudiFree',5)";
	
	c=createDatabase(database);
	printf("DB created: %d\n",c);
*/
	c=newValue(val);
	printf("%d",c);
	return 0;
}
