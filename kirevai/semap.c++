#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <semaphore.h>
using namespace std;
// Global semaphore object
sem_t semaphore;


void producer() {
    while (true) {
        // Acquire a resource from the semaphore
        sem_wait(&semaphore);
        
        // Produce the resource
        cout << "Producing resource..." << endl;
        
        // Simulate some work
        this_thread::sleep_for(chrono::seconds(1));
        
        // Release the resource to the semaphore
        sem_post(&semaphore);
    }
}

void consumer() {
    while (true) {
        // Acquire a resource from the semaphore
        sem_wait(&semaphore);
        
        // Consume the resource
        cout << "Consuming resource..." << endl;
        
        // Simulate some work
        this_thread::sleep_for(chrono::seconds(5));
        
        // Release the resource to the semaphore
        sem_post(&semaphore);
    }
}

int main() {
    // Initialize the semaphore with an initial count of 1 (one resource available)
    sem_init(&semaphore, 0, 1);
    
    // Create producer and consumer threads
    thread producer_thread(producer);
    thread consumer_thread(consumer);
    thread kire()
    
    // Wait for the threads to finish (which will never happen in this example)
    producer_thread.join();
    consumer_thread.join();
    
    // Destroy the semaphore
    sem_destroy(&semaphore);
    
    return 0;
}
