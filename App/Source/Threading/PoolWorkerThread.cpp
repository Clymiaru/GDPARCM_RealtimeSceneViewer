#include "pch.h"
#include "PoolWorkerThread.h"
#include "IFinishedTask.h"
#include "IWorkerAction.h"


PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finishedTask)
{
	this->id = id;
	this->finishedTask = finishedTask;
}

PoolWorkerThread::~PoolWorkerThread()
{

}

int PoolWorkerThread::getThreadID()
{
	return this->id;
}

void PoolWorkerThread::AssignTask(IWorkerAction* action)
{
	this->action = action;
}

void PoolWorkerThread::run()
{
	this->action->OnStartTask();
	this->finishedTask->OnFinished(this->id);
}
