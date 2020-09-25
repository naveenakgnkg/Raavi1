#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "../esb/bmd_parser.h"
#define FROM_ADDR    "<testgangahv@gmail.com>"
#define CC_ADDR      "<testgangahv@gmail.com>"

int sendMail(char *to, char *text) { 
  //text is file path for JSON

    printf("Sending to %s\n", to);

  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  
  curl = curl_easy_init();
  if(curl) {
    /* This is the URL for your mailserver */ 
    curl_easy_setopt(curl, CURLOPT_USERNAME, "testgangahv@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "Somil@1212");//enter password

    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
 
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);
 
    recipients = curl_slist_append(recipients, to);
    recipients = curl_slist_append(recipients, CC_ADDR);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
 
    //JSON file to be send 
    char* filepath= text;
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
  printf("...............................Mail sent successfully..............................\n");
 return 0;
}
/*
int main()
{
 // char *s = "HELL0";
  printf("%d",sendMail("testgangahv@gmail.com","/home/harshal/Desktop/payload.json"));
}*/

//  //smtp.gmail.com

// #include <stdio.h>
// #include <string.h>
// #include <curl/curl.h>
 
// /*
//  * For an SMTP example using the multi interface please see smtp-multi.c.
//  */ 
 
// /* The libcurl options want plain addresses, the viewable headers in the mail
//  * can very well get a full name as well.
//  */ 
// #define FROM_ADDR    "<testraavi1@gmail.com>"
// #define TO_ADDR      "<testraavi1@gmail.com>"
// #define CC_ADDR      "<testraavi1@gmail.com>"
 
// #define FROM_MAIL "Sender Person " FROM_ADDR
// #define TO_MAIL   "A Receiver " TO_ADDR
// #define CC_MAIL   "John CC Smith " CC_ADDR
 
// static const char *payload_text[] = {
  
//   "To: " TO_MAIL "\r\n",
//   "From: " FROM_MAIL "\r\n",
//   "Cc: " CC_MAIL "\r\n",
//   "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
//   "rfcpedant.example.org>\r\n",
//   "Subject: message\r\n",
//   "\r\n", /* empty line to divide headers from body, see RFC5322 */ 
//   "The body of the message starts here.\r\n",
//   "\r\n",
//   "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
//   "Check RFC5322.\r\n",
//   NULL
// };
 
// struct upload_status {
//   int lines_read;
// };
 
// static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
// {
//   struct upload_status *upload_ctx = (struct upload_status *)userp;
//   const char *data;
 
//   if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
//     return 0;
//   }
 
//   data = payload_text[upload_ctx->lines_read];
 
//   if(data) {
//     size_t len = strlen(data);
//     memcpy(ptr, data, len);
//     upload_ctx->lines_read++;
 
//     return len;
//   }
 
//   return 0;
// }

// void send(char *to, char *text) {
//     printf("Sending to %s\n", to);

//   CURL *curl;
//   CURLcode res = CURLE_OK;
//   struct curl_slist *recipients = NULL;
//   struct upload_status upload_ctx;
 
//   upload_ctx.lines_read = 0;
 
//   curl = curl_easy_init();
//   if(curl) {
//     /* This is the URL for your mailserver */ 
//     curl_easy_setopt(curl, CURLOPT_USERNAME, "testraavi1@gmail.com");
//     curl_easy_setopt(curl, CURLOPT_PASSWORD, "");//enter password

//     curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");
//     curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
//     /* Note that this option isn't strictly required, omitting it will result
//      * in libcurl sending the MAIL FROM command with empty sender data. All
//      * autoresponses should have an empty reverse-path, and should be directed
//      * to the address in the reverse-path which triggered them. Otherwise,
//      * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
//      * details.
//      */ 
//     //curl_easy_setopt(curl, CURLOPT_CAINFO, "/path/to/certificate.pem");
//     curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);
 
//     /* Add two recipients, in this particular case they correspond to the
//      * To: and Cc: addressees in the header, but they could be any kind of
//      * recipient. */ 
//     recipients = curl_slist_append(recipients, to);
//     recipients = curl_slist_append(recipients, CC_ADDR);
//     curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
 
//     /* We're using a callback function to specify the payload (the headers and
//      * body of the message). You could just use the CURLOPT_READDATA option to
//      * specify a FILE pointer to read from. */ 
//     curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
//     curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
//     curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
//     /* Send the message */ 
//     res = curl_easy_perform(curl);
 
//     /* Check for errors */ 
//     if(res != CURLE_OK)
//       fprintf(stderr, "curl_easy_perform() failed: %s\n",
//               curl_easy_strerror(res));
 
//     /* Free the list of recipients */ 
//     curl_slist_free_all(recipients);
 
//     /* curl won't send the QUIT command until you call cleanup, so you should
//      * be able to re-use this connection for additional messages (setting
//      * CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and calling
//      * curl_easy_perform() again. It may not be a good idea to keep the
//      * connection open for a very long time though (more than a few minutes
//      * may result in the server timing out the connection), and you do want to
//      * clean up in the end.
//      */ 
//     curl_easy_cleanup(curl);
//   }
 
//   return 0;
// }


// // // #include<stdio.h>

// // // void send(char *to, char *text) {
// // //     printf("Sending to %s\n", to);
// // // }
