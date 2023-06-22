#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

const int num_philosophers = 5;

mutex forks[num_philosophers];

void philosopher(int id) {
    while (true) {
        cout << "Philosopher " << id << " is thinking" << endl;
        // Simulate thinking
        this_thread::sleep_for(chrono::milliseconds(3000));
        cout << "Philosopher " << id << " is hungry" << endl;
        // Acquire left fork
        forks[id].lock();
        // Acquire right fork
        forks[(id + 1) % num_philosophers].lock();
        cout << "Philosopher " << id << " is eating" << endl;
        // Simulate eating
        this_thread::sleep_for(chrono::milliseconds(1000));
        // Release forks
        forks[id].unlock();
        forks[(id + 1) % num_philosophers].unlock();
    }
}

int main() {
    thread philosophers[num_philosophers];
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i] = thread(philosopher, i);
    }
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i].join();
    }
    return 0;
}
