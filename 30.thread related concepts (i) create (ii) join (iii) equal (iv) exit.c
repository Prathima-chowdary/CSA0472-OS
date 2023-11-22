#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *threadFunction(void *arg) {
    printf("Thread created with ID: %ld\n", pthread_self());
    sleep(2);
    pthread_exit(NULL);
}
int main() {
    pthread_t thread;
    int result;
    result = pthread_create(&thread, NULL, threadFunction, NULL);

    if (result != 0) {
        perror("Thread creation failed");
        return 1;
    }
    result = pthread_join(thread, NULL);

    if (result != 0) {
        perror("Thread join failed");
        return 1;
    }
    pthread_t currentThread = pthread_self();

    if (pthread_equal(thread, currentThread)) {
        printf("The created thread is equal to the current thread.\n");
    } else {
        printf("The created thread is not equal to the current thread.\n");
    }
    printf("Main thread is exiting.\n");
    return 0;
}