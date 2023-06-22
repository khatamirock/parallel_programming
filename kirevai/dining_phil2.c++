#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
class Philosopher {
private:
    std::string name;
    mutex & firstFork;
    mutex & secondFork;

public:
    Philosopher(std::string name, mutex & leftFork, mutex & rightFork)
        : name(std::move(name)), firstFork(leftFork), secondFork(rightFork) {}

    void dine() {
        while (true) {
            // Thinking
            std::cout << name << " is thinking." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            // Pick up forks
            bool acquiredFirstFork = firstFork.try_lock();
            bool acquiredSecondFork = secondFork.try_lock();

            if (acquiredFirstFork && acquiredSecondFork) {
                // Acquired both forks, start eating
                std::cout << name << " starts eating." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                std::cout << name << " finishes eating and puts down forks." << std::endl;

                // Release forks
                firstFork.unlock();
                secondFork.unlock();
            } else {
                // Unable to acquire both forks, release any acquired forks
                if (acquiredFirstFork) {
                    firstFork.unlock();
                }
                if (acquiredSecondFork) {
                    secondFork.unlock();
                }
                // Wait for a short period before retrying
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
};

int main() {
    mutex  fork1, fork2, fork3, fork4, fork5;

    Philosopher philosopher1("Aristotle", fork1, fork2);
    Philosopher philosopher2("Kant", fork2, fork3);
    Philosopher philosopher3("Buddha", fork3, fork4);
    Philosopher philosopher4("Marx", fork4, fork5);
    Philosopher philosopher5("Russell", fork5, fork1);

    std::thread t1(&Philosopher::dine, &philosopher1);
    std::thread t2(&Philosopher::dine, &philosopher2);
    std::thread t3(&Philosopher::dine, &philosopher3);
    std::thread t4(&Philosopher::dine, &philosopher4);
    std::thread t5(&Philosopher::dine, &philosopher5);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
