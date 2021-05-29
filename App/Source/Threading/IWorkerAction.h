#pragma once
class IWorkerAction
{
public:
	virtual ~IWorkerAction() = default;
	virtual void OnStartTask() = 0;
};

