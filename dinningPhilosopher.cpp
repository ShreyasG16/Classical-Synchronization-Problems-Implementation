#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h> 
using namespace std;

const int n = 5; // No. of philosophers

mutex forks[n];      // One mutex per fork
mutex table_lock;    // Global lock to prevent deadlock

void think(int id) 
{
    cout << "Philosopher " << id << " is thinking.\n";
    sleep(1); // Simulating.. thinking
}

void eat(int id) 
{
    cout << "Philosopher " << id << " is eating.\n";
    sleep(2); // Simulating.. eating
}

void philosopher(int id) 
{
    int left = id;
    int right = (id + 1) % n;

    while(true) 
    {
        think(id);

        // (i) Lock global table to prevent deadlock
        table_lock.lock();

        // (ii) Lock both forks
        forks[left].lock();
        forks[right].lock();

        // (iii) Release global lock so others can try
        table_lock.unlock();

        eat(id);

        forks[left].unlock();
        forks[right].unlock();
    }
}

int main() 
{
    vector<thread> threads;

    for(int i = 0; i < n; ++i) 
    {
        threads.push_back(thread(philosopher, i));
    }

    for(int i = 0; i < n; ++i) 
    {
        threads[i].join();
    }

    return 0;
}
