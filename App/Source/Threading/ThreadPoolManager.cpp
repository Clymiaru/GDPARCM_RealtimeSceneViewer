#include "pch.h"
#include "ThreadPoolManager.h"
#include "Utils/Log.h"

ThreadPoolManager& ThreadPoolManager::GetInstance()
{
	static ThreadPoolManager instance;
	return instance;
}

ThreadPoolManager::~ThreadPoolManager()
{
	this->map.clear();
}

void ThreadPoolManager::startScheduler(std::string name, int numWorkers)
{
	if (this->map.find(name) == this->map.end())// non existent name
	{
		this->map[name] = new ThreadPool(name + " threads", numWorkers);
		this->map[name]->startScheduler();
	}
	else
	{
		this->map[name]->startScheduler();
	}
}

void ThreadPoolManager::stopScheduler(std::string name)
{
	if (this->map.find(name) == this->map.end())// non existent name
	{
		LOG("Threadpool with name: " << name << " does not exist!");
	}
	else
	{
		this->map[name]->stopScheduler();
	}
}

void ThreadPoolManager::ScheduleTask(std::string name, IWorkerAction* action)
{
	if (this->map.find(name) == this->map.end())// non existent name
	{
		LOG("Threadpool with name: " << name << " does not exist!");
	}
	else
	{
		this->map[name]->scheduleTask(action);
	}
}

ThreadPoolManager::ThreadPoolManager()
{

}
