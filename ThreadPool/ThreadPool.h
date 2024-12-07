/*!
 * @brief 
 *
 * 
 *
 * @author LiuYe
 * @date 2024.12.07
 * @copyright (c) 2013-2024 Honghu Yuntu Corporation
 */
#pragma once

#include <thread>
#include <vector>
#include <atomic>
#include <queue>
#include <functional>
#include <mutex>
#include <unordered_map>
/*
 * 构成：
 * 1. 管理者线程 -> 子线程 1 个
 *      - 控制工作线程的数量 -> 增加或减少
 * 2. 若干个工作线程 -> 子线程 n 个
 *      - 从任务队列中取任务处理
 *      - 任务队列为空 堵塞
 *      - 线程同步(互斥锁)
 *      - 当前数量 空闲的线程数量
 *      - 最小 最大线程数量
 * 3. 任务队列 -> stl->queue
 *      - 互斥锁
 *      - 条件变量
 * 4. 线程池开关
 */ 

class ThreadPool
{
public:
    ThreadPool(int min, int max);
    ~ThreadPool();

    void addTask(const std::function<void()>& task);

private:
    void manager();
    void worker();

    int m_nMinThread;
    int m_nMaxThread;
    std::atomic<bool> m_bStop;
    std::atomic<int> m_nIdleThread;
    std::atomic<int> m_nCurThread;
    std::atomic<int> m_nExitThread;

    std::unique_ptr<std::thread> m_pManager;

    std::unordered_map<std::thread::id, std::thread> m_oWorkers;
    std::mutex m_oWorkersMutex;

    std::queue<std::function<void()>> m_oTasks;
    std::mutex m_oQueueMutex;
    std::condition_variable m_oCondition;

    std::vector<std::thread::id> m_oIDs;
    std::mutex m_oIDsMutex;
};
