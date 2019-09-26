#include "Precompiled.h"
#include "WorkerThread.h"
#include "AwesomeNet.h"
#include "IONotifier.h"

WorkerThread::WorkerThread()
	: _simpleio(nullptr)
{
}

WorkerThread::WorkerThread(AwesomeNet* simpleio)
	: _simpleio(simpleio)
{
}

void WorkerThread::SetNetEngine(AwesomeNet* simpleio)
{
	_simpleio = simpleio;
}

void* WorkerThread::Process()
{
	while(_simpleio->isRunning.load())
	{
		_simpleio->GetIONotifier()->run();
	}

	return nullptr;
}
