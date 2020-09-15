// #include <mysql.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include "../esb/bmd_parser.h"




// char* compare(transformvalue,tfkey)
// {
//     if(strcmp(transformvalue,tfkey1)==0)
//     {
//         printf("-----------xml------------\n");
//         address = payloadToXml(bmd);
//         printf("address:%s\n",address);
//     }
//     if(strcmp(transformvalue,tfkey2)==0)
//     {
//         printf("-----------json------------\n");
//         address= payloadToJson(bmd);
//         printf("address:%s\n",address);
//     }
// }

// void transportJob(transportkey,tpkey,address)
// {

//     if(strcmp(transportkey,tpkey1)==0)
//     {
//         printf("-----------mail------------\n");
//         sendMail(transportvalue,address);
//         printf("transportvalue:%s address:%s\n",transportvalue,address);
//     }
//     if(strcmp(transportkey,tpkey2)==0)
//     {
//         printf("-----------http------------\n");
//         requestWeb(transportvalue);
//         printf("transportvalue:%s address:%s\n",transportvalue,address);
//     }
// }



// int decision(BMD* bmd,char* transformvalue,char* transformkey,char* transportvalue,char* transportkey)
// {
//     char* tfkey1="xml";
//     char* tfkey2="json";
//     char* tpkey1="email";
//     char* tpkey2="url";
//     char* tfv=transformvalue;
//     char* tfk=transformkey;
//     char* tpv=transportvalue;
//     char* tpk=transportkey;
//     printf("\n\ntfv:%s\ntfk:%s\ntpv:%s\ntpk:%s\n\n",tfv,tfk,tpv,tpk);
//     char* address;
//     printf("\n---------------------in decision-----------------------\n");
//     printf("transformvalue:%s \ntransformkey:%s\ntransportvalue:%s\ntransportkey:%s\n",transformvalue,transformkey,transportvalue,transportkey);
//     //printf("COMPARE\nstrcmp(transformvalue,tfkey1):%d\n",strcmp(transformvalue,tfkey1));
//     printf("tfkey1=xml:%s\n fkey2=json:%s \npkey1=email:%s\n  tpkey2=url:%s\n",tfkey1,tfkey2,tpkey1,tpkey2);
//     printf("transformvalue:%s  tfkey1:%s\n",transformvalue,tfkey1);
//     printf("transportkey:%s  tpkey1:%s\n",transportkey,tpkey1);
//     //printf("COMPARE\nstrcmp(transformvalue,tfkey2):%d\n",strcmp(transformvalue,tfkey2));
   
    

//     return 0;
// }