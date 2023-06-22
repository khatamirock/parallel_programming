#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

std::queue<int> buffer;
const int MAX_SIZE = 5;
std::mutex mtx;
std::condition_variable cv;

// Process an item
void process_item(int item)
{
    std::cout << "Processing item: " << item << std::endl;
}

// Producer function
void producer()
{
    int item = 0;

    while (true)
    {
        // Produce an item
        item++;

        // Acquire the lock to access the buffer
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if the buffer is full
        while (buffer.size() == MAX_SIZE)
        {
            std::cout << "Buffer is full. Producer is waiting..." << std::endl;
            cv.wait(lock);
        }

        // Add the item to the buffer
        buffer.push(item);
        std::cout << "Produced item: " << item << std::endl;

        // Notify the consumer that an item is available
        cv.notify_all();

        // Release the lock
        lock.unlock();

        // Sleep for some time before producing the next item
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Consumer function
void consumer()
{
    while (true)
    {
        // Acquire the lock to access the buffer
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if the buffer is empty
        while (buffer.empty())
        {
            std::cout << "Buffer is empty. Consumer is waiting..." << std::endl;
            cv.wait(lock);
        }

        // Consume an item from the buffer
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed item: " << item << std::endl;

        // Notify the producer that a space is available in the buffer
        cv.notify_all();

        // Release the lock
        lock.unlock();

        // Process the consumed item
        process_item(item);

        // Sleep for some time before consuming the next item
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


int main()
{
    // Create producer and consumer threads
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    // Start the threads
    producer_thread.join();
    consumer_thread.join();

    return 0;
}

