# Multithreaded Server using pthreads and sockets.  

Implementation of a multithreaded server that allows multiple users to make requests at the same time. 
Each user can request access to the database and the request can be PUT or GET.
The implementation makes use of the reader/writter logic where only one writter can
modify the database or multiple readers can access it and read data at the same time, as well as the producer/consumer logic to synchronize the incoming requests. Also the implementation gives priority to readers. For the tests, a multithreaded client is used to establish a TCP Connection over the server and start feeding requests.


## Main Flow

### Consumers - Producers

 * Producer Thread - Main thread that awaits for requests from a client through a TCP connection. Produces a request descriptor and awaits if the buffer is full or appends it and notifies a consumer thread to process the request.
 * Consumer Threads - Multiple threads that are responsible for extracting and serving the requests from the buffer in parallel if the buffer is not empty. Depending on the request descriptor a consumer thread can be either a reader or a writter.
 * Buffer - Circular FIFO Queue of finite size. Just like all the global resources it must be protected by mutual exclusion when modified.

<p align="center">
  <img src="https://github.com/billgewrgoulas/Multithreaded-Server/blob/main/server-client/producer-consumer.png" />
</p>


### Readers - Writers (Priority to Readers)

 * Readers – Readers are those processes/users which only read the data.
 * Writers – Writers are those processes which also write, that is, they change the data.
 * It is allowed for 2 or more readers to access shared data, simultaneously as they are not making any change and even after the reading the
   database will remain unchanged.
 * But if one writer(Say w1) is writing then it should lock and no other writer or reader can access the database until w1 has finished
   writing. 

<p align="center">
  <img src="https://github.com/billgewrgoulas/Multithreaded-Server/blob/main/server-client/Readers-Writers-Operating-System-No-DB-OS-Operating-System.png" />
</p>

<p align="center">
  <img src="https://github.com/billgewrgoulas/Multithreaded-Server/blob/main/server-client/Readers-Writers-Operating-System-Readers-DB-OS-Operating-System.png" />
</p>

<p align="center">
  <img src="https://github.com/billgewrgoulas/Multithreaded-Server/blob/main/server-client/Readers-Writers-Operating-System-Writer-DB-OS-Operating-System.png" />
</p>

### Multithreaded Client

* To test the server we will use a multithreaded client. Each thread will establish a TCP connection in parallel and make a random request (PUT or Get) to the server.

<p align="center">
  <img src="https://github.com/billgewrgoulas/Multithreaded-Server/blob/main/server-client/VmHa3.png" />
</p>

### Custom Signal Handler CTRL-Z

 * The signal handler is responsible to block the default handler with sigmask and assign a custom method to handle CTRL-Z.
 * When the signal arrives the servers outputs the statistics then awakes and terminates all threads safely using global flag variables and <b>pthread_join()</b>

# Usage

Run the server with ./server then in a new terminal do ./client . 
You can also use the custom signal handler with CTRL-Z to terminate the server and see the stats for various number of consumer threads and queue size.
