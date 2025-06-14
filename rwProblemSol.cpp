//Problem : This solution has writers starvation problem.It is biased towards Readers as it blocks writer and readers may keep coming.

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>
using namespace std;

int readcount = 0;
mutex mtx;              // mutex for readcount
mutex wrt;              // binary semaphore for writer access

void reader(int id) 
{
    // Entry section
    mtx.lock();

    readcount++;
    if (readcount == 1) 
    {
        wrt.lock();  
    }

    mtx.unlock();

    // Critical section
    cout << "Reader " << id << " is reading\n";
    sleep(1);  

    // Exit section
    mtx.lock();

    readcount--;
    if(readcount == 0) 
    {
        wrt.unlock();  
    }

    mtx.unlock();
}

void writer(int id) 
{
    wrt.lock(); 

    cout << "Writer " << id << " is writing\n";
    sleep(2);  

    wrt.unlock();  
}

int main() 
{
    vector<thread> threads;

    // Launching.. readers
    for (int i = 0; i < 3; i++) 
    {
        threads.push_back(thread(reader, i));
    }

    // Launching.. writers
    for (int i = 0; i < 2; i++) 
    {
        threads.push_back(thread(writer, i));
    }

    // Joining.. all
    for (int i = 0; i < threads.size(); ++i) 
    {
        threads[i].join();
    }

    return 0;
}
