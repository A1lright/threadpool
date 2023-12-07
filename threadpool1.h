//
// Created by lin on 12/6/23.
//

#ifndef THREADPOOL_THREADPOOL1_H
#define THREADPOOL_THREADPOOL1_H
#include<iostream>
#include<atomic>
#include<functional>
#include<thread>
#include<vector>
#include"threadsafe_queue.h"

class join_threads
{
    std::vector<std::thread>&threads;
public:
    explicit join_threads(std::vector<std::thread>&threads_):threads(threads_)
    {}
    ~join_threads()
    {
        for(unsigned long i=0;i<threads.size();++i)
        {
            if(threads[i].joinable())
                threads[i].join();
        }
    }
};

class thread_pool
{
    std::atomic_bool done;
    threadsafe_queue<std::function<void()>> work_queue;
    std::vector<std::thread> threads;
    join_threads joiner;

    void worker_thread()
    {
        while(!done)
        {
            std::function<void()>task;
            if(work_queue.try_pop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();//Tells the operating system that it is willing to give up its current CPU time;
            }
        }
    }

public:
    thread_pool():done(false), joiner(threads)
    {
        unsigned const thread_count=std::thread::hardware_concurrency();
        try
        {
            for(unsigned i=0;i<thread_count;++i)
            {
                threads.push_back(std::thread(&thread_pool::worker_thread,this));
            }
        }
        catch (...)
        {
            done=true;
            throw;
        }
    }

    ~thread_pool()
    {
        done=true;
    }

    template<typename FunctionType>
    void submit(FunctionType f)
    {
        work_queue.push(std::function<void()>(f));
    }
};

#endif //THREADPOOL_THREADPOOL1_H
