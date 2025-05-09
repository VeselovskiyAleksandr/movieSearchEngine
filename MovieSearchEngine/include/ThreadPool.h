﻿// ThreadPool.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once
#include <iostream>
using namespace std;

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
//#ifndef THREAD_POOL_H
//#define THREAD_POOL_H

#include <vector>
#include <queue>
//#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
//#include <functional>
//#include <stdexcept>

class ThreadPool {
public:
    ThreadPool(size_t);
 // ThreadPool(int);
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        ->std::future<typename result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    // отслеживание потоков для присоединения к ним
    vector<thread> workers;
    // the task queue
    queue<function<void()>> tasks;
    // синхронизация
    mutex queue_mutex;
    condition_variable condition;
    bool stop;
};

// конструктор запускает некоторое количество процессов
//inline ThreadPool::ThreadPool(size_t threads)
inline ThreadPool::ThreadPool(size_t threads)
    : stop(false)
{
 //   for (size_t i = 0; i < threads; ++i)
     for (int i = 0; i < threads; ++i)
        workers.emplace_back(
      //      [this]
            [&]
            {
                for (;;)
                {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
            //                [this] { return this->stop || !this->tasks.empty(); });
                            [&] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                        task();
                }
            }
            );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
-> future<typename result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = make_shared<packaged_task<return_type()>>(
        bind(forward<F>(f), forward<Args>(args)...)
        );
        future<return_type> res = task->get_future();
    {
        unique_lock<mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if (stop)
            throw runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
 //   return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        unique_lock<mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (thread& worker : workers)
        worker.join();
}

//#endif
