#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(const int min, const int max)
    : m_nMinThread(min), m_nMaxThread(max), m_bStop(false),
    m_nIdleThread(0), m_nCurThread(0), m_nExitThread(0)
{
    // 创建管理线程
    m_pManager = std::make_unique<std::thread>(&ThreadPool::manager, this);
    // 创建工作线程
    for (int i = 0; i < min; ++i)
    {
        {
            std::lock_guard<std::mutex> lock(m_oWorkersMutex);
            std::thread t(&ThreadPool::worker, this);
            m_oWorkers.emplace(t.get_id(), std::move(t));
        }
        m_nCurThread++;
        m_nIdleThread++;
    }
}

ThreadPool::~ThreadPool()
{
    // 设置停止标志
    m_bStop = true;
    // 通知所有线程
    m_oCondition.notify_all();

    // 先停止管理线程
    if (m_pManager && m_pManager->joinable())
    {
        m_pManager->join();
    }

    // 然后停止所有工作线程
    {
        std::lock_guard<std::mutex> lock(m_oWorkersMutex);
        for (auto& it : m_oWorkers)
        {
            std::thread& t = it.second;
            if (t.joinable())
            {
                std::cout << "*************** 线程 " << t.get_id() << " 将要退出了..." << '\n';
                t.join();
            }
        }
        m_oWorkers.clear();
    }
}

void ThreadPool::addTask(const std::function<void()>& task)
{
    {
        std::lock_guard<std::mutex> locker(m_oQueueMutex);
        m_oTasks.emplace(task);
    }
    m_oCondition.notify_one();
}

void ThreadPool::manager()
{
    while (!m_bStop.load())
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        const int nIdle = m_nIdleThread.load();
        const int cur = m_nCurThread.load();

        if (nIdle > cur / 2 && cur > m_nMinThread)
        {
            // 每次销毁两个线程
            m_nExitThread += 2;
            m_oCondition.notify_all();

            std::lock_guard<std::mutex> lock(m_oIDsMutex);
            {
                std::lock_guard<std::mutex> workersLock(m_oWorkersMutex);
                for (auto it = m_oWorkers.begin(); it != m_oWorkers.end() && m_nExitThread > 0; )
                {
                    const std::thread::id id = it->first;
                    std::thread& t = it->second;
                    if (t.joinable())
                    {
                        std::cout << "===============线程 " << id << " 被销毁了 ...\n";
                        t.join();
                        it = m_oWorkers.erase(it);
                        m_nCurThread--;
                        m_nExitThread--;
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }
        else if (nIdle == 0 && cur < m_nMaxThread)
        {
            // 增加新的工作线程
            std::thread t(&ThreadPool::worker, this);
            {
                std::lock_guard<std::mutex> lock(m_oWorkersMutex);
                m_oWorkers.emplace(t.get_id(), std::move(t));
            }
            m_nCurThread++;
            m_nIdleThread++;
        }
    }
}

void ThreadPool::worker()
{
    while (true)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> locker(m_oQueueMutex);
            m_oCondition.wait(locker, [this]() { return !m_oTasks.empty() || m_bStop.load() || m_nExitThread.load() > 0; });

            if (m_nExitThread.load() > 0)
            {
                m_nCurThread--;
                m_nIdleThread--;
                m_nExitThread--;
                std::cout << "线程退出了... " << std::this_thread::get_id() << '\n';
                return;
            }

            if (m_bStop.load() && m_oTasks.empty())
                return;

            if (!m_oTasks.empty())
            {
                std::cout << "取出了一个任务..." << '\n';
                task = std::move(m_oTasks.front());
                m_oTasks.pop();
            }
            else
            {
                continue;
            }
        }
        if (task)
        {
            m_nIdleThread--;
            task();
            m_nIdleThread++;
        }
    }
}
static void calc(const int x, const int y)
{
    const int z = x + y;
    std::cout << "z = " << z << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main()
{
    ThreadPool pool(4, 8);
    for (int i = 0; i < 10; i++)
    {
        auto obj = std::bind(calc, i, i * 2);
        pool.addTask(obj);
    }
    std::getchar();
    return 0;
}
