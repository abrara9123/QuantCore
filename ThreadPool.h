//
// Created by fiora on 4/20/2026.
//
#ifndef QUANTCORE_THREADPOOL_H
#define QUANTCORE_THREADPOOL_H
#include "TaskQueue.h"
#include <vector>
#include <thread>
#include <mutex>


class ThreadPool {
private:
    std::vector<std::jthread> ThreadVector;
    TaskQueue TaskQueueObject;
    std::condition_variable cv2;



public:
    ThreadPool(int n);
    ~ThreadPool();
    void addTask(std::function<void()> task);

};

inline ThreadPool::ThreadPool(int n) {

    for (int i = 0; i < n; i++) {
        //Use a lambda function to know what code to run on the new threads being made.
        //Each thread will handle a function that we pass in and it will run then go out of scope hten another task is made
        std::jthread t1([this] {
    while (true) {
    std::function<void()> task;
    TaskQueueObject.waitPop(task);

        if (!TaskQueueObject.waitPop(task)) break;
 task();
}
});
        // To store the threads into a vector we need to use the move then we cannt copy them due to memory safety issue
        ThreadVector.push_back(std::move(t1));
    }
}

inline void ThreadPool::addTask(std::function<void()> task) {
    TaskQueueObject.push(task);

}

inline ThreadPool::~ThreadPool() {
    TaskQueueObject.stopped = true;
    TaskQueueObject.cv.notify_all();

}

#endif //QUANTCORE_THREADPOOL_H
