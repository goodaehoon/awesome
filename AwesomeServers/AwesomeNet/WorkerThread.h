#pragma once

#include "Thread.h"

class AwesomeNet;

class WorkerThread : public Thread
{
private:
	AwesomeNet* _simpleio;

public:
	WorkerThread();
	WorkerThread(AwesomeNet* simpleio);

	void SetNetEngine(AwesomeNet* simpleio);
	void* Process();
};

