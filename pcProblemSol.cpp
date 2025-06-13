#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <unistd.h> 
using namespace std;

const int maxSize = 5;
queue<int> buffer;

class Semaphore 
{
private:
    int count;
    mutex mtx;
    condition_variable cv;

public:
    Semaphore(int c)
    {
        count = c;
    }

    void wait() 
    {
        unique_lock<mutex> lock(mtx);

        while(count == 0) 
        {
            cv.wait(lock);
        }

        count--;
    }

    void signal() 
    {
        unique_lock<mutex> lock(mtx);

        count++;

        cv.notify_one();
    }
};

Semaphore sem_empty(maxSize);  // initially all slots are empty
Semaphore sem_full(0);          // initially no items
mutex mtx;                      // binary semaphore for buffer access

void producer(int id) 
{
    for(int i = 0; i < 5; ++i) 
    {
        sem_empty.wait();       // wait for empty slot
        mtx.lock();             // enter critical section

        int item = id * 10 + i;
        buffer.push(item);
        cout << "Producer " << id << " produced " << item << endl;

        mtx.unlock();           // exit critical section
        sem_full.signal();      // signal that an item is produced

        sleep(1);               // simulating some delay
    }
}

void consumer(int id) 
{
    for (int i = 0; i < 5; ++i) 
    {
        sem_full.wait();        // wait for filled slot
        mtx.lock();             // enter critical section

        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed " << item << endl;

        mtx.unlock();           // exit critical section
        sem_empty.signal();     // signal that a slot is now free

        sleep(2);    // simulating some delay          
    }
}

int main() 
{
    vector<thread> threads;

    // Launching.. producers
    for (int i = 0; i < 2; ++i) {
        threads.push_back(thread(producer, i));
    }

    // Launching.. consumers
    for (int i = 0; i < 2; ++i) {
        threads.push_back(thread(consumer, i));
    }

    for (int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }

    return 0;
}
