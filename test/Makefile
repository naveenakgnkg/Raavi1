
output: main.o createdb.o xmlParse.o
	gcc -o main main.o createdb.o -std=c99  `mysql_config --cflags --libs` xmlParse.o -lxml2

main.o:main.c
	gcc -c main.c
xmlParse.o:xmlParse.c
	gcc -c -Wall $(xml2-config --cflags) $(xml2-config --libs) xmlParse.c -lxml2
createdb.o:createdb.c
	gcc -c createdb.c -std=c99  `mysql_config --cflags --libs`

clean:
	rm *.o output
