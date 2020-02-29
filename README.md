# TCP-UDP Data Transformation
This is a network-based application that offers several different data transformation services to users. Each of these micro-services will run as its own server, and you will use a master server to coordinate each session of data transformation services.

## How to run this program:
* Unzip the zip file and go to the location in terminal window.
* Then run following commands to compile all 8 *.cpp files.
```
g++ mainserver.cpp -o mainserver
g++ mainclient.cpp -o mainclient
g++ identity.cpp -o identity
g++ reverse.cpp -o reverse
g++ lower.cpp -o lower
g++ upper.cpp -o upper
g++ caesar.cpp -o caesar
g++ yours.cpp -o yours
```
* Then run following commands to run all 8 runnable files.
```
./mainserver
./mainclient
./identity
./reverse
./lower
./upper
./caesar
./yours
```

* make sure you run “mainserver” before “mainclient”
* it’s easier to run all 8 client&servers in 8 different terminal windows

## This set of programs can:
Take input string and commands to convert the input string with
1. Identity: echoes back input string.
2. Reverse: reverse a string
3. Upper: convert all lower-case characters to upper-case
4. Lower: convert all upper-case characters to lower-case
5. Caesar: convert a string into encryption of casesar cypher
6. Yours: convert a given string to camel case
* 1-6 can be combined and mixed in different orders to convert a string by command.
* it can detect if there is a delay in one of the servers and sends message to server and client and terminates the server.

## This set of programs can’t:
allow the dynamic creation, registration, and termination of microservices
while the master server is running, rather than having them all
started in advance and/or statically assigned.

* The testing environment are home and school but IP address of local host (127.0.0.1) has been constantly used regardless of environment. Testing is done with random sentences and random combination of commands.