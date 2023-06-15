
#pragma once

#define LOG_ON_COPPELIA true
#define LOG_ON_CMD true

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
	void log(const std::string& message);
	
	~CoppeliaSimClient();
};