#include <stdio.h>
#include <string.h>
#include "munit.h"
#include <libxml/parser.h>
#include "bmd3.h"

char *get_str_data(char *file)
{
  char *value;
  char str_data[50];
  int i=0;
  FILE *fp = fopen(file, "r");
  for(i=0;i<2;i++)
  {
  	fgets(str_data,50,fp);
  	
  	
  }
  fclose(fp);	
  return strdup(str_data);
}

xml_to_json_setup(const MunitParameter params[], void *user_data)
{
  char *file = "bmd.xml";
  BMD  * bd = processXML(file);
  xml2json(bd->bmd_payload->data);
  char *value="001-01-12342";
  /* Copy file data into string */
  char *json_data=(char *)malloc(sizeof(char)*50) ;
  sprintf(json_data," \"Payload\":\"%s\"\n",value);
  return strdup(json_data);
}

/* Test function */
static MunitResult
test_xml_to_json(const MunitParameter params[], void *fixture)
{
  char *json_data=(char *)fixture;
  
  //json_data = (char *)fixture;

  char *test_data = get_str_data("Payload.json");

  munit_assert_string_equal(json_data, test_data);
   //find_size("Payload.json");
  return MUNIT_OK;
}

static void
xml_to_json_tear_down(void *fixture)
{

  free(fixture);
}

MunitTest bmd_tests[] = {
   

    {
        "/xml_to_json_test",    /* name */
        test_xml_to_json,       /* test function */
        xml_to_json_setup,      /* setup function for the test */
        xml_to_json_tear_down,  /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/bmd_tests",           /* name */
    bmd_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}
