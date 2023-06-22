#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Declare the semaphore
sem_t semaphore;

// Function executed by threads
void* thread_function(void* arg) {
    // Acquire the semaphore
    sem_wait(&semaphore);

    // Critical section: shared resource access
    printf("Accessing shared resource \n");

    // Release the semaphore
    sem_post(&semaphore);

    return NULL;
}

int main() {
    // Initialize the semaphore
    sem_init(&semaphore, 0, 1);

    // Create multiple threads
    pthread_t threads[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}

