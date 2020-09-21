Updates
------------------------------------------------------------------------
1. Working 2 threads
________________________________________________________________________

# Important Commands:

1.`kodev build`

2.`kodev run`

3.`curl --insecure -F "bmd_file=@//home/pc/Desktop/bmd.xml" https://localhost:8888/bmd`

4.`fuser -k -n tcp 8888`


-------------------------------------------------------------------------------

### Installing essential libraries that you will need

 Open a shell and run `sudo apt update`
1. Ensure that you have installed the essential headers and libraries: `sudo apt install build-essential`
2. Install required Libraries:

       sudo apt update
       sudo apt install build-essential
       sudo apt install libssl-dev
       sudo apt install wget
       sudo apt install curl

    Libxml2

    `sudo apt-get install libxml2`
    `sudo apt-get install libxml2-dev`
    
    [Pthread](https://askubuntu.com/questions/453860/unable-to-locate-package-pthread)
    
    `sudo apt-get install libpthread-stubs0-dev`
    
    Libcurl
    
    MySql
    
    

3. You will be writing unit tests for all your C code using [munit](https://nemequ.github.io/munit/#getting-started).
4. Install Kore Web framework as [described here](https://docs.kore.io/3.3.1/install.html). You will use it to write an HTTP endpoint for receiving the requests for the ESB.

5.[Kore's simple guide](https://docs.kore.io/3.3.1/).

### Source code layout

code in the repository layout:

```

someuser@OX:~/temp/esb_proj/esb_app$ tree
├── curl
│   └── curl1.c
├── db_schema.sql
├── esb_endpoint
│   ├── bmd_files
│   │   ├── 1599334640_2042160951
│   │   │   └── bmd.xml
│   │   └── 1600446116_1950302937
│   │       ├── bmd1.xml
│   │       ├── bmd2.xml
│   │       └── bmd.xml
│   ├── build_tests.sh
│   ├── cert
│   │   ├── key.pem
│   │   └── server.pem
│   ├── conf
│   │   ├── build.conf
│   │   └── esb_endpoint.conf
│   ├── dh2048.pem
│   ├── esb.code-workspace
│   ├── esb_endpoint.so
│   ├── kore.pid
│   ├── munitTesting
│   │   ├── bmd3.h
│   │   ├── bmd.xml
│   │   ├── mail
│   │   ├── munit.c
│   │   ├── munit.h
│   │   ├── Payload.json
│   │   ├── test
│   │   ├── test_changes_available2taken.c
│   │   ├── test_json
│   │   ├── test_json.c
│   │   ├── test_processXML
│   │   ├── test_processXML.c
│   │   ├── test_send_email.c
│   │   ├── test_validation
│   │   └── test_validation.c
│   ├── payload.json
│   ├── Payload.json
│   ├── payload.xml
│   ├── src
│   │   ├── adapter
│   │   │   ├── email.c
│   │   │   ├── email.h
│   │   │   ├── httpService.c
│   │   │   ├── send.c
│   │   │   ├── transform.c
│   │   │   ├── transform.h
│   │   │   └── transport.h
│   │   ├── database
│   │   │   ├── database.h
│   │   │   ├── fetchRoute.c
│   │   │   ├── routeData.c
│   │   │   └── update_esb_request.c
│   │   ├── esb
│   │   │   ├── bmdparse.c
│   │   │   ├── bmd_parser.h
│   │   │   ├── esb.c
│   │   │   ├── esbfun.h
│   │   │   ├── validation.c
│   │   │   ├── validation.h
│   │   │   └── worker.c
│   │   ├── esb_endpoint.c
│   │   ├── insert.c
│   │   ├── test
│   │   │   ├── munit.c
│   │   │   └── munit.h
│   │   └── xmljson.c
│   └── tmp_files
├── queue
│   ├── queue
│   └── queue.c
└── README.md

```

The above structure is for reference.

## Run Kodev
```
cd esb_endpoint/
kodev build
kodev run
```

Open another shell window and run:
`curl --insecure -F "bmd_file=@/some/file/path/dummy_data.txt" https://localhost:8888/bmd`
Use `&` for running multiple curl commands at once.

Check the logs in first shell; it should show that the file was successfully received.

A solution is to kill all processes which are holding on to port 8888. It can be done easily by running the following
command:
`fuser -k -n tcp 8888`

