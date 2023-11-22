#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

pthread_mutex_t mutex;         
sem_t writeMutex;              
int readersCount = 0; 
int sharedData = 0;
void *reader(void *arg);
void *writer(void *arg);

int main() {
    pthread_mutex_init(&mutex, NULL);
    sem_init(&writeMutex, 0, 1);
    pthread_t readerThreads[NUM_READERS];
    pthread_t writerThreads[NUM_WRITERS];
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&readerThreads[i], NULL, reader, NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writerThreads[i], NULL, writer, NULL);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readerThreads[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writerThreads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&writeMutex);

    return 0;
}

void *reader(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);  
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeMutex);   
        }
        pthread_mutex_unlock(&mutex);  
        printf("Reader %ld read: %d\n", pthread_self(), sharedData);

        pthread_mutex_lock(&mutex); 
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeMutex);   
        }
        pthread_mutex_unlock(&mutex); 
        usleep(1000);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&writeMutex); 
        sharedData++;
        printf("Writer %ld wrote: %d\n", pthread_self(), sharedData);

        sem_post(&writeMutex); 
        usleep(2000);
    }

    pthread_exit(NULL);
}