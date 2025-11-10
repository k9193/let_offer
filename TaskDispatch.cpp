#include <iostream>
#include <vector>
#include <queue>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
using namespace std;
/*
实现生产者消费者模式
*/
class Task
{
public:
    Task() {}
    virtual ~Task() {}
    virtual void operator()() = 0;
};

template <typename F, typename... Args>
class TaskFunctor : public Task
{
public:
    TaskFunctor(F &&f, Args &&...args) : f_(std::forward<F>(f)), args_(std::forward<Args>(args)...) {}

    void operator()() override
    {
        std::apply(f_, args_); // 解包调用
    }

private:
    F f_;
    std::tuple<Args...> args_;
};

class ThreadPool
{
public:
    ThreadPool(int threadNum)
    {
        stop_ = true;
        for (int i = 0; i < threadNum; i++)
        {
            threads_.emplace_back(std::thread(&ThreadPool::ThreadEntry, this));
        }
        stop_ = false;
    }
    ~ThreadPool()
    {
        stop_ = true;
        conditional_.notify_all();
        for (auto &thread : threads_)
        {
            thread.join();
        }
        threads_.clear();
        tasks_.clear();
    }

public:
    template <typename F, typename... Args>
    void AddTask(F &&f, Args &&...args)
    {
        auto task = std::make_unique<TaskFunctor<F, Args...>>(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mutex_);
            tasks_.push(task);
        }
        conditional_.notify_one();
    }

protected:
    void ThreadEntry()
    {
        this->TaskRun();
    }
    void TaskRun()
    {
        while (!stop_)
        {
            std::unique_ptr<Task> task = nullptr;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                conditional_.wait(lock, [&]
                                  { return stop_ || !tasks_.empty(); }); // 返回true wait才会返回 此时2个条件 1队列非空 并且线程池已开启
                if (!tasks_.empty())
                {
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
            }
            if (task)
            {
                (*task)();
            }
        }
    }

private:
    std::vector<std::thread> threads_;
    std::atomic<bool> stop_;
    std::mutex mutex_;
    std::condition_variable conditional_;
    std::queue<std::unique_ptr<Task>> tasks_;
};