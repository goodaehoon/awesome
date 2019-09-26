#include "Precompiled.h"
#include "AwesomeNet.h"
#include "Dispatcher.h"
#include "IONotifier.h"
#include "Session.h"
#include "SessionManager.h"
#include "DBManager.h"
#include "RedisManager.h"
#include "WorkerThread.h"
#include "DispatchThread.h"
#include "DBThread.h"
#include "RedisThread.h"
#include "Dispatcher.h"
#include "TimerQueue.h"
#include "Acceptor.h"
#include "AcceptorManager.h"
#include "Connector.h"
#include "ConnectorManager.h"

AwesomeNet::AwesomeNet()
	: ioNotifier(new IONotifier)	
	, workerThread(new WorkerThread(this))
	, dispatchThread(new DispatchThread(this))
	, dbThread(new DBThread(this))
	, redisThread(new RedisThread(this))
	, sessionManager(new SessionManager(this))
	, dbManager(new DBManager)
	, redisManager(new RedisManager)
	, messageQueue(new MessageQueue)
	, timerQueue(new TimerQueue)
	, acceptorManager(new AcceptorManager)
	, isRunning(false)
{
	Init();
}

AwesomeNet::~AwesomeNet()
{
	Stop();

	delete acceptorManager;
	delete timerQueue;
	delete messageQueue;
	delete redisManager;
	delete dbManager;
	delete sessionManager;
	delete redisThread;
	delete dbThread;
	delete dispatchThread;
	delete workerThread;	
	delete ioNotifier;
}

bool AwesomeNet::Init()
{
	return true;
}

SessionManager* AwesomeNet::GetSessionManager()
{
	return sessionManager;
}

MessageQueue* AwesomeNet::GetMessageQueue()
{
	return messageQueue;
}

TimerQueue* AwesomeNet::GetTimerQueue()
{
	return timerQueue;
}

IONotifier* AwesomeNet::GetIONotifier()
{
	return ioNotifier;
}

DBManager* AwesomeNet::GetDBManager()
{
	return dbManager;
}

RedisManager* AwesomeNet::GetRedisManager()
{
	return redisManager;
}

bool AwesomeNet::Start()
{
	// 동작플래그를 켜고, 필요한 스레드를 동작시킨다
	SetRunning(true);

	dispatchThread->Start();
	workerThread->Start();	
	dbThread->Start();	
	redisThread->Start();

	return true;
}

void AwesomeNet::Stop()
{
	// 동작플래그 OFF
	SetRunning(false);

	// 각 스레드가 종료되기를 기다린다
	workerThread->Join();
	dispatchThread->Join();
	redisThread->Join();
	dbThread->Join();
}

void AwesomeNet::SetRunning(bool flag)
{
	isRunning.store(flag);
}

void AwesomeNet::SetDBDispatcher(IDBDispatcher* disp)
{
	dbThread->SetDBDispatcher(disp);
}

void AwesomeNet::SetInterDispatcher(IInterDispatcher* disp)
{
	dispatchThread->SetInterDispatcher(disp);
}

void AwesomeNet::SetTimerDispatcher(ITimerDispatcher* disp)
{
	dispatchThread->SetTimerDispatcher(disp);
}

void AwesomeNet::SetRedisDispatcher(IRedisDispatcher* disp)
{
	redisThread->SetRedisDispatcher(disp);
}

bool AwesomeNet::Open(unsigned short port, IDispatcher* disp)
{
	return Open(nullptr, port, disp);
}

bool AwesomeNet::Open(const char* ip, unsigned short port, IDispatcher* disp)
{
	Acceptor* acceptor = acceptorManager->CreateAcceptor(ioNotifier, sessionManager, disp);
	if (acceptor->Open(ip, port) == false)
		return false;

	return true;
}

bool AwesomeNet::Connect(const char* ip, unsigned short port, IDispatcher* disp)
{
	Connector* connector = connectorManager->create(disp);
	if (connector->Connect(ip, port) == false)
		return false;

	return true;
}


