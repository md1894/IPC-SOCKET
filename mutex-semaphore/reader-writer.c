#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

/*
This program provides a possible solution for first readers writers problem 
using mutex and semaphore.
I have used 10 readers and 5 producers to demonstrate the solution. 
You can always play with these values.
*/

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *writer(void *wno)
{   
    sem_wait(&wrt);
    /*
    critical section code entry
    */
    cnt = cnt*2;
    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),cnt);
    /*
    critical section code exit
    */
    sem_post(&wrt);

}

void *reader(void *rno)
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader++;
    /*
    when first reader enters to read data
    it will block the writers
    */
    if(numreader == 1) {
        sem_wait(&wrt); 
    }
    pthread_mutex_unlock(&mutex);

    // Reading Section
    printf("Reader %d: read cnt as %d\n",*((int *)rno),cnt);

    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    // If this is the last reader, it will wake up the writer.
    if(numreader == 0) {
        sem_post(&wrt); 
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   

    pthread_t read[10],write[5];

    pthread_mutex_init(&mutex, NULL);
    //sem_init(sem_t *sem, int pshared, unsigned int value);
    /*
    sem : Specifies the semaphore to be initialized.

    pshared : This argument specifies whether or 
    not the newly initialized semaphore is shared between processes or 
    between threads. 
    A non-zero value means the semaphore is shared between processes and 
    a value of zero means it is shared between threads.

    value : Specifies the value to assign to the newly initialized semaphore.
    */
    sem_init(&wrt,0,1);

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; 
    //Just used for numbering the producer and consumer

    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }
    // main thread will wait for all the threads to complete operation
    for(int i = 0; i < 10; i++) {
        // second agrument is the pointer that will store the exit status
        // of the target thread, i.e. value passed to pthread_exit()
        // by the terminated thread 
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}
