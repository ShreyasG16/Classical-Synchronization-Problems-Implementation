#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>
using namespace std;

int readcount = 0;            // no. of active readers
int waitingWriters = 0;       // no. of writers waiting

mutex mtx;                    // protects readcount and waitingWriters
mutex wrt;                    // binary semaphore to restrict readers & writers when writing going on.
mutex readerEntry;            // prevents new readers if a writer is waiting

void reader(int id) 
{
    // Entry section
    readerEntry.lock();            // block new readers if writer is waiting
    readerEntry.unlock();          // allow if no writer is waiting

    mtx.lock();
    readcount++;
    if (readcount == 1) {
        wrt.lock();                // first reader locks writers
    }
    mtx.unlock();

    // Critical section
    cout << "Reader " << id << " is reading\n";
    sleep(1);                      // simulating.. reading

    // Exit section
    mtx.lock();

    readcount--;
    if (readcount == 0) {
        wrt.unlock();              // last reader unlocks writers
    }

    mtx.unlock();
}

void writer(int id) 
{
    // Entry section
    mtx.lock();
    waitingWriters++;              // signal writer is waiting
    if (waitingWriters == 1) 
    {
        readerEntry.lock();        // block new readers
    }
    mtx.unlock();

    wrt.lock();                    // only one writer allowed
    cout << "Writer " << id << " is writing\n";
    sleep(2);                      // simulate writing
    wrt.unlock();

    // Exit section
    mtx.lock();
    waitingWriters--;              // writer done
    if(waitingWriters == 0) 
    {
        readerEntry.unlock();      // allow readers again
    }
    mtx.unlock();
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

    for (int i = 0; i < threads.size(); ++i) 
    {
        threads[i].join();
    }

    return 0;
}
