#pragma once

class IONotifier;
class SessionManager;
class IDispatcher;
class Connector;

class ConnectorManager
{
	typedef list<Connector* > ConnectorList;

private:
	IONotifier* ioMux;
	SessionManager* ssMgr;
	ConnectorList connectors;

public:
	ConnectorManager(IONotifier* ioMux, SessionManager* ssMgr);
	~ConnectorManager();

	Connector* create(IDispatcher* disp);
};

