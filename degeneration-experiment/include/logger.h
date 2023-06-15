#pragma once

#define LOG_ON_COPPELIA true
#define LOG_ON_CMD true

#include <string>

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

extern "C"
{
#include "extApi.h"
#include "extApiPlatform.h"
}


class Logger
{
private:
	int clientID;
public:
	Logger(int clientID);
	void log(const std::string& message);
};