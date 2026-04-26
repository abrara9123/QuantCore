
#include  <iostream>
#include "ThreadPool.h"
#include "TaskQueue.h"
#include  <random>
using namespace std;


int main() {

    ThreadPool testThread(10);

    for (int i = 0; i < 10; i++) {
        testThread.addTask([i]{
            cout << "Task " << i << " running\n";
        });
    };
    return 0;
}



