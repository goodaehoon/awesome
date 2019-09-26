#include "Precompiled.h"
#include "ConnectorManager.h"
#include "IONotifier.h"
#include "SessionManager.h"
#include "Dispatcher.h"
#include "Connector.h"

ConnectorManager::ConnectorManager(IONotifier* ioMux, SessionManager* ssMgr)
	: ioMux(ioMux)
	, ssMgr(ssMgr)
{
}

ConnectorManager::~ConnectorManager()
{
	for (auto itr : connectors)
	{
		SAFE_DELETE(itr);
	}
}

Connector* ConnectorManager::create(IDispatcher* disp)
{
	//Connector* connector = new Connector(ioMux, ssMgr, disp);

	//connector->SetType(EVENT_OBJECT_CONNECTOR);

//	connectors.push_back(connector);

	//return connector;

	return nullptr;
}
