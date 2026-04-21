//
// Created by fiora on 4/20/2026.
//
#ifndef QUANTCORE_THREADPOOL_H
#define QUANTCORE_THREADPOOL_H
#include "TaskQueue.h"
#include <vector>
#include <thread>

class ThreadPool {
private:
    std::vector<std::thread> ThreadVector;
    TaskQueue TaskQueueObject;

public:
    ThreadPool(int n);
    ~ThreadPool();
    void addTask();

};

inline ThreadPool::ThreadPool(int n) {

    for (int i = 0; i < n; i++) {
        //Use a lambda function to know what code to run on the new threads being made.
        //Each thread will handle a function that we pass in and it will run then go out of scope hten another task is made
        std::thread t1([this] {
    while (true) {
    std::function<void()> task;
    TaskQueueObject.waitPop(task);
    task();
}
});
        // To store the threads into a vector we need to use the move then we cannt copy them due to memory safety issue
        ThreadVector.push_back(std::move(t1));
    }

}

inline ThreadPool::~ThreadPool() {

}

#endif //QUANTCORE_THREADPOOL_H
