//gcc -Wall -I/usr/include/libxml2 -o mail test_send_email.c -lxml2 munit.c -lcurl
#include <stdio.h>
#include "munit.h"
//#include <libxml/parser.h>
#include <curl/curl.h>
//#include "bmd2.h"
//#include "bmd3.h"

#define FROM_ADDR    "<rockyrohan890@gmail.com>"
#define CC_ADDR      "<rockyrohan890@gmail.com>"

int sendMail(char *to, char *text) { 
  //text is file path for JSON

    printf("Sending to %s\n", to);

  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  
  curl = curl_easy_init();
  if(curl) {
    /* This is the URL for your mailserver */ 
    curl_easy_setopt(curl, CURLOPT_USERNAME, "rockyrohan890@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "rockyrohan890@8123");//enter password

    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
 
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);
 
    recipients = curl_slist_append(recipients, to);
    recipients = curl_slist_append(recipients, CC_ADDR);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
 
    //JSON file to be send 
    char* filepath=text;
    FILE *fd = fopen(filepath, "r");
//         curl_easy_setopt(curl, CURLOPT_READDATA, fp);
    curl_easy_setopt(curl, CURLOPT_READDATA,fd);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
    /* Send the message */ 
    res = curl_easy_perform(curl);
 
    /* Check for errors */ 
    if(res != CURLE_OK)
     { fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
              return -1;
     }
    /* Free the list of recipients */ 
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
  }
 return 1;
}


/* Test function */
static MunitResult
test_sendMail(const MunitParameter params[], void *fixture)
{
  int rc = sendMail("sohan.jumanal@gmail.com", "Payload.json");
  munit_assert(rc != 0);
  return MUNIT_OK;
}




MunitTest v_tests[] = {
    

    {
        "/test_sendMail",   /* name */
        test_sendMail,      /* test function */
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
    "/test",           /* name */
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
