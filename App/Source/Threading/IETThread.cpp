#include "pch.h"
#include "IETThread.h"

IETThread::IETThread()
{
}

IETThread::~IETThread()
{
}

void IETThread::Start()
{
	std::thread(&IETThread::run, this).detach(); //detach thread for independent execution. without this, join() function must be called.
}

void IETThread::Sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
