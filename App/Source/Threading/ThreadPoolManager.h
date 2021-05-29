#pragma once
#include "ThreadPool.h"
#include <unordered_map>


class ThreadPoolManager
{
	typedef std::unordered_map<std::string, ThreadPool*> ThreadPoolMap;

public:
	ThreadPoolManager(const ThreadPoolManager& other) = delete;
	ThreadPoolManager(ThreadPoolManager&& other) noexcept = delete;
	ThreadPoolManager& operator=(const ThreadPoolManager& other) = delete;
	ThreadPoolManager& operator=(ThreadPoolManager&& other) noexcept = delete;

	static ThreadPoolManager& GetInstance();
	~ThreadPoolManager();

	void startScheduler(std::string name, int numWorkers);
	void stopScheduler(std::string name);
	void ScheduleTask(std::string name, IWorkerAction* action);

private:
	ThreadPoolManager();
	ThreadPoolMap map;
};

