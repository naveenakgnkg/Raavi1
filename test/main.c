#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"function.h"

int main()
{
	//char* name="bmd.xml";
	//char* database;
	char* val="INSERT INTO Cars VALUES(100,'AudiFree',5)";
	int s,c;
	/*printf("In the main:\n");
	//scanf("%s",name);
	s=readXml(name);
	printf("Read: %d\n",s);
	printf("Enter the DB name: ");
	/*scanf("%s",database);
	c=createDatabase(database);
	printf("DB created: %d\n",c);
*/
	c=newValue(val);
	printf("%d",c);
	return 0;
}
