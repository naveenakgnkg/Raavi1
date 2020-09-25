SQL_FUN     = ../esb/db_header.h ../esb/routeData.c ../esb/insert.c
XML_FUN     =../adapter/email.c ../esb/validation.c     
LIBXML     =   `xml2-config --libs` `xml2-config --cflags`
LIBSQL     =  `mysql_config --cflags --libs`
a:  mtest.c  
	gcc ${SQL_FUN} ${XML_FUN} -lcurl mtest.c munit.h munit.c -o a ${LIBSQL} ${LIBXML}

clean:
	rm a