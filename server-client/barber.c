
int maxInside = 0;

semaphore s1 , s2 , s3;
s1.count = 0;//client
s2.count = 1;//chair

struct semaphore{
    int count;
}

void wait(semaphore s){
    s.count--;
    while(s.count<0){
        //wait here
    }
}

void signal(semaphore s){
    s.count++;
}

void barber(){

    while(1){
        wait(s1);
        //cut
        sleep(10000);
        signal(s2);
    }

}

void client_enters(){

    if(maxInside == 5){
        return;
    }

    signal(s1);

    //better use binary sem for the chair
    if(s2.count == -1){
        s2.count++;
    }
    wait(s2);

    sleep(10000);
    client_leaves();
}

void client_leaves(){
    maxInside--;
    wait(s1);
    ///signal(s2); barber gets to call the next client
}


/////////////////////////////////////////only one process in the critical section

s3.count = 0;

void wait(semaphore s){
    
    while(s.count<0){ //here w actually define a binary semaphore
        //wait here
    }
    s.count--;
}

void signal(semaphore s){
    s.count++;
}

void process(){

    while(1){
        wait(s3);
        //do job
        signal(s3);
    }
}

///mesa

bool occupied = false;
int someone_inside;

void proc(){

    while(1){
        while(occupied){
            cwait(someone_inside);
        }
        occupied = true;
        //do job
        sleep(1000);
        occupied = false;
        cnotify(someone_inside);
    }


}

