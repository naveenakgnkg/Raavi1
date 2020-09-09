#include <stdio.h>
#include "munit.h"
#include <libxml/parser.h>
#include "bmd3.h"
//#include "bmd_parser.h"

/*int main()
{
  char *file = "bmd.xml";
  BMD  * bd = processXML(file);
  printf("......%s",bd->bmd_envelope->MessageID);
  //bd *x = processXML(file);
   bd->envelope=  extract_envelope(file);
    bd->Payload= extract_payload(file);
  //bd = processXML(file);
  //printf(%s)
  return 0;
}*/
static void *
parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
{
  char *file = "bmd.xml";
  BMD  * bd = processXML(file);
   // bd->envelope=  extract_envelope(file);
   // bd->Payload= extract_payload(file);
  
  return bd;
}

BMD *get_bmd(void)
{
  BMD *bmd_file = (BMD *)malloc(sizeof(BMD));
  envelope *values = (envelope *)malloc(sizeof(envelope));
  values->Sender = "A";
  values->Destination = "6393F82F-4687-433D-AA23-1966330381FE1";
  values->CreationDateTime = "2020-08-12T05:18:00+00001";
  values->MessageID = "A9ECAEF2-107A-4452-9553-043B6D25386E1";
  values->MessageType = "xml";
  values->ReferenceID = "INV-PROFILE-8897121";
  values->Signature = "63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c1";
  bmd_file->bmd_envelope = values;
  bmd_file->bmd_payload = "001-01-12342";

  return bmd_file;
}

static MunitResult
test_parse_bmd_xml(const MunitParameter params[], void *fixture)
{
  BMD *test_bmd = (BMD *)fixture;
  BMD *expected_bmd = get_bmd();
  /* is_bmd_valid returns 1 if valid */
  munit_assert_string_equal(test_bmd->bmd_envelope->Sender,
                            expected_bmd->bmd_envelope->Sender);
  munit_assert_string_equal(test_bmd->bmd_envelope->Destination,
                             expected_bmd->bmd_envelope->Destination);
  munit_assert_string_equal(test_bmd->bmd_envelope->MessageType,
                            expected_bmd->bmd_envelope->MessageType);
  munit_assert_string_equal(test_bmd->bmd_envelope->CreationDateTime,
                             expected_bmd->bmd_envelope->CreationDateTime);
  munit_assert_string_equal(test_bmd->bmd_envelope->MessageID,
                             expected_bmd->bmd_envelope->MessageID);
  munit_assert_string_equal(test_bmd->bmd_envelope->Signature,
                             expected_bmd->bmd_envelope->Signature);
  munit_assert_string_equal(test_bmd->bmd_envelope->ReferenceID,
                             expected_bmd->bmd_envelope->ReferenceID);
  munit_assert_string_equal(test_bmd->bmd_payload->data,expected_bmd->bmd_payload);
  
  return MUNIT_OK;
}

static void
parse_bmd_xml_tear_down(void *fixture)
{
  BMD *bd = (BMD *)fixture;

  //free(bd->envelope);
  //free(bd->Payload);
  free(bd);

}


/* Put all unit tests here. */
MunitTest bmd_tests[] = {
    {
        "/parse_bmd_xml_test",   /* name */
        test_parse_bmd_xml,      /* test function */
        parse_bmd_xml_setup,     /* setup function for the test */
        parse_bmd_xml_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
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

