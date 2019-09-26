#pragma once

#include "Thread.h"

class AwesomeNet;
class IDBDispatcher;

class DBThread : public Thread
{
private:
	AwesomeNet* _simpleio;
	IDBDispatcher* _dbDispatcher;

public:
	DBThread(AwesomeNet* simpleio);
	void SetDBDispatcher(IDBDispatcher* disp);

	void* Process();
};

