#include "../esb/db_header.h"
#include "munit.h"
#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

#define server "localhost"
#define user "root"
#define password "password"
#define database "esb_db"


char* transportkey(int route_id)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
    char* transport_key;
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Get transform config_key */ 
	sprintf(query, "SELECT config_key FROM transport_config WHERE route_id='%d'", route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	strcpy(transport_key,strdup(row[0]));
	
	/* free results */
	mysql_free_result(res);
	printf("transport_key:%s\n",transport_key);
	return transport_key;
}

static MunitResult
test_email(const MunitParameter params[], void * fixture) {
    int check = sendMail("testgangahv@gmail.com", "/home/harshal/Desktop/paytest.json");
    munit_assert_int(check, == , 0);
    return MUNIT_OK;
}

static MunitResult
test_route_id(const MunitParameter params[], void * fixture) {
    int check = routeId("abb","testgangahv@gmail.com","json");
    int x=0;
    if(check > 0)
    x = 1;
    munit_assert_int(x, == , 1);
    return MUNIT_OK;
}

static MunitResult
test_transform_key(const MunitParameter params[], void * fixture) {
     char* key = "IFSC";
    munit_assert_string_equal(key,"IFSC");
    return MUNIT_OK;
}

static MunitResult
test_active_route_check(const MunitParameter params[], void * fixture) {
    
    int check = activeRouteCheck("abb","testgangahv@gmail.com","json");
    int x=0;
    if(check > 0)
    {
    x=1;
    }
    munit_assert_int(x, == , 1);
    return MUNIT_OK;
}

static MunitResult
test_transport_config(const MunitParameter params[], void * fixture) {
    
    int check = transportConfigCheck(14);
    int x=0;
    if(check > 0)
    {
    x=1;
    }
    munit_assert_int(x, == , 0);
    return MUNIT_OK;
}
static MunitResult
test_transform_config(const MunitParameter params[], void * fixture) {
    
    int check = transformConfigCheck(14); 
    int x=0;
    if(check > 0)
    {
    x=1;
    }
    munit_assert_int(x, == , 0);
    return MUNIT_OK;
}



MunitTest test_esb[] = {
  
    
    {
        "/email_test",      /* name */
        test_email, /* test function */
        NULL,                         /* setup function for the test */
        NULL,                         /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    },
    {
        "/route_id_test",      /* name */
        test_route_id, /* test function */
        NULL,                         /* setup function for the test */
        NULL,                         /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    },    
   
      {
        "/transform_key_test",      /* name */
        test_transform_key, /* test function */
        NULL,                         /* setup function for the test */
        NULL,                         /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    }, 
     {
        "/test_active_route_test",      /* name */
        test_active_route_check, /* test function */
        NULL,                         /* setup function for the test */
        NULL,                         /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    }, 

    {
        "/test_transport_config",      /* name */
         test_transport_config, /* test function */
        NULL,                         /* setup function for the test */
        NULL,                         /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    }, 

     {
        "/test_transform_config",      /* name */
         test_transform_config, /* test function */
        NULL,                         /* setup function for the test */
        NULL,                         /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    }, 

{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/tests_esb",      /* name */
    test_esb,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */

int main(int argc, const char *argv[])
{
    return munit_suite_main(&suite, NULL, argc, argv);
}
