#include <stdio.h>
#include "munit.h"
#include <libxml/parser.h>
//#include "bmd2.h"
#include "bmd3.h"

/*char * attributes[7] =  {
    "MessageID",
    "MessageType",
    "Sender",
    "Destination",
    "CreationDateTime",
    "Signature",
    "ReferenceID"
};*/
 
/*
* @ breif : checking whether is a leaf node generated in DOM  
    if yes return 1 else 0    
*/

static void *
is_bmd_valid_setup(const MunitParameter params[], void *user_data)
{
  char *file = "bmd.xml";
  BMD  * bd = processXML(file);
 // printf("\n%ssohn\n",bd->bmd_envelope->Sender);
  return bd;
}

/* Test function */
static MunitResult
test_is_bmd_valid(const MunitParameter params[], void *fixture)
{
  BMD *test_bmd = (BMD *)fixture;
  /* is_bmd_valid returns 1 if valid */
  //printf("\n%ssoh\n",test_bmd->bmd_envelope->Sender);
  munit_assert(validate_xml_file(test_bmd) == 1);
  return MUNIT_OK;
}

static void
is_bmd_valid_tear_down(void *fixture)
{
  free(fixture);
}

/* Test setup function creates bmd and returns it */



/* Put all unit tests here. */
MunitTest v_tests[] = {
    

    {
        "/is_bmd_valid_test",   /* name */
        test_is_bmd_valid,      /* test function */
        is_bmd_valid_setup,     /* setup function for the test */
        is_bmd_valid_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },

   
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/bmd_tests",           /* name */
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
