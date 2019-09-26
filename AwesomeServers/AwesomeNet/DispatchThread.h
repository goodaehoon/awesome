#pragma once

#include "Thread.h"

class AwesomeNet;
class IInterDispatcher;
class ITimerDispatcher;

class DispatchThread : public Thread
{
private:
	AwesomeNet* _simpleio;
	IInterDispatcher* _interDispatcher;
	ITimerDispatcher* _timerDispatcher;

public:
	DispatchThread(AwesomeNet* simpleio);
	void SetInterDispatcher(IInterDispatcher* disp);
	void SetTimerDispatcher(ITimerDispatcher* disp);

	void* Process();
};

