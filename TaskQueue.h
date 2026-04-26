//
// Created by fiora on 4/18/2026.
//
#ifndef QUANTCORE_TASKQUEUE_H
#define QUANTCORE_TASKQUEUE_H
#include <iostream>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>




class TaskQueue {
private:
    std::queue<std::function<void()>> queue_;
    std::mutex mutex_;


public:
    //Using a reference if we use lamda is bad since a referenece to a temporray varaialbe is bad
    std::condition_variable cv;
    bool stopped = false;
    void push(std::function<void()> task);
    bool pop(std::function<void()>& task);
    bool waitPop(std::function<void()>& task);
    bool empty();

};

inline void TaskQueue::push(std::function<void()> task) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(task);
    cv.notify_one();
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


inline bool TaskQueue::waitPop(std::function<void()>& task) {
    //For the conditon varaible using the lock guard is not good
    std::unique_lock<std::mutex> lock(mutex_);
    //Need to use the this to acess a memeber variable if we are using a lambda

    cv.wait(lock, [this]{ return !queue_.empty() || stopped; });
    if (stopped) return false;
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
