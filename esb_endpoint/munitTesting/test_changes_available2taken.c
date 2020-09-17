//gcc -Wall -I/usr/include/libxml2 -o test test_changes_available2taken.c -lxml2 munit.c $(mysql_config --cflags) $(mysql_config --libs)

#include <stdio.h>
#include "munit.h"
#include <libxml/parser.h>
//#include "bmd2.h"
#include "bmd3.h"



/* Test function */
static MunitResult
test_update_the_status(const MunitParameter params[], void *fixture)
{
  int rc = change_available_to_taken(56,"RECEIVED");
  munit_assert(rc != 0);
  return MUNIT_OK;
}




MunitTest v_tests[] = {
    

    {
        "/test_update_the_status",   /* name */
        test_update_the_status,      /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },

   
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/test\n",           /* name */
    v_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}
