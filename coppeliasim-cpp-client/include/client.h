
#pragma once

#define LOG_ON_COPPELIA false
#define LOG_ON_CMD false

#include <iostream>
#include <windows.h>
#include <string>

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

extern "C"
{
#include "extApi.h"
#include "extApiPlatform.h"
}

class CoppeliaSimClient
{
private:
	int clientID;
	simxChar* connectionAddress;
	simxInt connectionPort;
public:
	CoppeliaSimClient(const std::string& connectionAddress = "127.0.0.1", const int& connectionPort = 19999);
	bool initialize();

	int getClientID();
	
	void startSimulation();
	void stopSimulation();

	void setIntegerSignal(const std::string& signalName, const int& signalValue);
	void setFloatSignal(const std::string& signalName, const double& signalValue);
	void setStringSignal(const std::string& signalName, const std::string& signalValue);

	int getIntegerSignal(const std::string& signalName);
	double getFloatSignal(const std::string& signalName);
	std::string getStringSignal(const std::string& signalName);

	void log_msg(const std::string& message) const;
	
	~CoppeliaSimClient();
};