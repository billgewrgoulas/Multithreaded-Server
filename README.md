# Multithreaded Server using pthreads and sockets , First Assignment in Operating Systems

Implementation of a multithreaded server that allows multiple users to make requests at the same time. 
Each user can request access to the database and the request can be PUT or GET.
The implementation makes use of the reader/writter logic where only one writter can
modify the database or multiple readers can access it and read data at the same time, as well as the producer/consumer logic to synchronize the incoming requests.
Also the implementation gives priority to readers. For the tests , a multithreaded client is used for request feeding .


When a new request arrives a new thread is utilized or reused by the server to serve the request.

![alt text](https://github.com/billgewrgoulas/Multithreaded-Server/blob/main/des.png?raw=true)

# Usage

Run the server with ./server then in a new terminal do ./client . You can also use the custom signal handler with CTRL-Z to terminate the server and see the stats.

