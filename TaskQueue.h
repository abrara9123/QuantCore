//
// Created by fiora on 4/18/2026.
//
#ifndef QUANTCORE_TASKQUEUE_H
#define QUANTCORE_TASKQUEUE_H
#include <iostream>
#include <queue>
#include <mutex>
#include <functional>


class TaskQueue {
private:
    std::queue<std::function<void()>> queue_;
    std::mutex mutex_;


public:
    //Using a reference if we use lamda is bad since a referenece to a temporray varaialbe is bad
    void push(std::function<void()> task);
    bool pop(std::function<void()>& task);
    bool empty();

};

inline void TaskQueue::push(std::function<void()> task) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(task);
}

inline bool TaskQueue::pop(std::function<void()> &task) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        return false;
    }
    task = queue_.front();
    queue_.pop();
    return true;
}

 inline bool TaskQueue::empty() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        return true;
    }
    return false;
}


#endif //QUANTCORE_TASKQUEUE_H
