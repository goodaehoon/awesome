#pragma once

#include "Thread.h"

class AwesomeNet;
class IRedisDispatcher;

class RedisThread : public Thread
{
private:
	AwesomeNet* _simpleio;
	IRedisDispatcher* _redisDispatcher;

public:
	RedisThread(AwesomeNet* simpleio);
	void SetRedisDispatcher(IRedisDispatcher* disp);

	void* Process();
};

