# Multithreaded-Server

Implementation of a multithreaded server that allows multiple users to make requests at the same time. 
Each user can request access to the database and the request can be PUT or GET.
The implementation makes use of the reader/writter logic where only one writter can
modify the database or multiple readers can access it and read data at the same time, as well as the producer/consumer logic to synchronize the incoming requests.
Also the implementation doesnt allow starvation to occur. The client code is provided as well.
Run the server with ./server then in a new terminal do ./client . You can also use CTRL - Z to terminate the server and see the stats.
