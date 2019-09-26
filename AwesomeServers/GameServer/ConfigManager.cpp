#include "Precompiled.h"
#include "ConfigManager.h"
#include "ConfigReader.h"
#include "Application.h"

ConfigManager::ConfigManager()
{
}

bool ConfigManager::ReadConfig(char* fullpath)
{
	ConfigReader serverConf;
	serverConf.Read(fullpath);

	// �⺻���� ������ �д´�
	networkConfig.ip = serverConf.Get<string>("NETWORK.ip", "127.0.0.1");
	networkConfig.port = serverConf.Get<int>("NETWORK.port", 5001);

	// �α� ������ �д´�
	logConfig.logPath = serverConf.Get<string>("LOG.log_path", "./log");

	// Mysql DB ������ �д´�
	mysqlConfig[ACCOUNT_DB].ip = serverConf.Get<string>("MariaDB.account_db_ip", "127.0.01");
	mysqlConfig[ACCOUNT_DB].port = serverConf.Get<int>("MariaDB.account_db_port", 3306);
	mysqlConfig[ACCOUNT_DB].user = serverConf.Get<string>("MariaDB.account_db_user", "root");
	mysqlConfig[ACCOUNT_DB].passwd = serverConf.Get<string>("MariaDB.account_db_passwd", "rneogns");
	mysqlConfig[ACCOUNT_DB].dbname = serverConf.Get<string>("MariaDB.account_db_name", "test");

	mysqlConfig[GAME_DB].ip = serverConf.Get<string>("MariaDB.game_db_ip", "127.0.01");
	mysqlConfig[GAME_DB].port = serverConf.Get<int>("MariaDB.game_db_port", 3306);
	mysqlConfig[GAME_DB].user = serverConf.Get<string>("MariaDB.game_db_user", "root");
	mysqlConfig[GAME_DB].passwd = serverConf.Get<string>("MariaDB.game_db_passwd", "rneogns");
	mysqlConfig[GAME_DB].dbname = serverConf.Get<string>("MariaDB.game_db_name", "test");

	// Redis ������ �д´�
	redisConfig[MASTER_REDIS].ip = serverConf.Get<string>("master_redis_ip", "127.0.0.1");
	redisConfig[MASTER_REDIS].port = serverConf.Get<int>("master_redis_port", 6379);

	return true;
}
