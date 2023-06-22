#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include <chrono>
using namespace std;

class Philosopher
{
private:
    string name;
    mutex & leftFork;
    mutex & rightFork;
    /* data */
public:
Philosopher(string name,std::mutex& leftfrk,std::mutex& rightfrk)
:name(move(name)),leftFork(leftfrk),rightFork(rightfrk){}

    void run(){
        cout<<name<<" is hungry litte boiiii finding forks\n\n";
        hungry();

    }
    void hungry(){
        while (true)
        {
            leftFork.try_lock();
            bool gotit=rightFork.try_lock();
            if (gotit){
                break;
            }
            leftFork.unlock();
         
        }
        leftFork.lock();
        rightFork.lock();
        eat();
        leftFork.unlock();
        rightFork.unlock();
    }

    void eat(){
        cout<<"yaayy got the spoons"<<name<<"\n";
        this_thread::sleep_for(chrono::seconds(3));

    }

};

 
 

int main() {
    std::mutex fork1 ,fork2, fork3, fork4, fork5;

    Philosopher philosopher1("Aristotle", fork1, fork2);
    Philosopher philosopher2("Kant", fork2, fork3);
    Philosopher philosopher3("Buddha", fork3, fork4);
    Philosopher philosopher4("Marx", fork4, fork5);
    Philosopher philosopher5("Russell", fork5, fork1);

    thread t1(&Philosopher::run, &philosopher1);
    thread t2(&Philosopher::run, &philosopher2);
    thread t3(&Philosopher::run, &philosopher3);
    thread t4(&Philosopher::run, &philosopher4);
    thread t5(&Philosopher::run, &philosopher5);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}





