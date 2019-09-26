#pragma once

#include "GlobalDefines.h"
#include <atomic>

class AwesomeNet;
class ConfigManager;
class ClientDispatcher;
class DBDispatcher;
class RedisDispatcher;
class InterDispatcher;
class TimerDispatcher;
class GameManager;

class Application
{
private:
	ConfigManager* configManager;
	AwesomeNet* networkEngine;
	ClientDispatcher* clientDispatcher;
	DBDispatcher* dbDispatcher;
	RedisDispatcher* redisDispatcher;
	InterDispatcher* interDispatcher;
	TimerDispatcher* timerDispatcher;
	GameManager* gameManager;

public:
	std::atomic_bool isRunning;

public:
	Application();
	~Application();

	static Application& GetInstance();

	bool Init(int argc, char* argv[]);
	void Process();
	void Close();

	void SetRunningFlag(bool flag);

	ConfigManager* GetConfigManager();
	GameManager* GetGameManager();
	AwesomeNet* GetNetworkEngine();

private:
	bool ReadConfig(int argc, char* argv[]);
	bool OpenNetwork();
	bool ConnectDB();
	bool ConnectRedis();
	bool InitGameObjects();
	void Start();

};

#define CONFIG_MANAGER() Application::GetInstance().GetConfigManager()
#define GAME_MANAGER() Application::GetInstance().GetGameManager()
#define NETWORK_ENGINE() Application::GetInstance().GetNetworkEngine()
#define MESSAGE_QUEUE() NETWORK_ENGINE()->GetMessageQueue()
#define TIMER_QUEUE() NETWORK_ENGINE()->GetTimerQueue()
#define DB_MANAGER() NETWORK_ENGINE()->GetDBManager()
#define REDIS_MANAGER() NETWORK_ENGINE()->GetRedisManager()
#define USER_MANAGER() GAME_MANAGER()->GetUserManager()