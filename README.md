# Multithreaded-Server

A simple multithreaded server that allows multiple users to make requests at the same time. 
Each user can request access to the database and the request can be PUT or GET.
The implementation makes use of the reader/writter logic where only one writter can
modify the database or multiple readers can access it and read data at the same time.
