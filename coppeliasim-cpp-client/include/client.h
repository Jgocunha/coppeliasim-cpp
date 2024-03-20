
#pragma once

#define LOG_ON_COPPELIA false
#define LOG_ON_CMD false

#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm> 

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

extern "C"
{
#include "extApi.h"
#include "extApiPlatform.h"
}

namespace coppeliasim_cpp
{
	enum class LogMode
	{
		NO_LOGS = 0,
		LOG_CMD,
		LOG_COPPELIA,
		LOG_COPPELIA_CMD
	};

	struct Position
	{
		float x, y, z;

		Position(float x, float y, float z) : x(x), y(y), z(z) {}
		Position() : x(0), y(0), z(0) {}
	};

	struct Orientation
	{
		float alpha, beta, gamma;

		Orientation(float alpha, float beta, float gamma) : alpha(alpha), beta(beta), gamma(gamma) {}
		Orientation() : alpha(0), beta(0), gamma(0) {}
	};

	struct Pose
	{
		Position position;
		Orientation orientation;

		Pose(Position position, Orientation orientation) : position(position), orientation(orientation) {}
		Pose() : position(), orientation() {}
	};

	class CoppeliaSimClient
	{
	private:
		int clientID;
		simxInt connectionPort;
		LogMode logMode;
		std::unique_ptr<simxChar[]> connectionAddress;
	public:
		CoppeliaSimClient(const std::string& connectionAddress = "127.0.0.1", 
			int connectionPort = 19999, 
			LogMode logMode = LogMode::LOG_COPPELIA_CMD);

		bool initialize();
		bool isConnected() const;
		int getClientID() const;

		void startSimulation() const;
		void stopSimulation() const;

		void setIntegerSignal(const std::string& signalName, int signalValue) const;
		void setFloatSignal(const std::string& signalName, const float& signalValue) const;
		void setStringSignal(const std::string& signalName, const std::string& signalValue) const;
		int getIntegerSignal(const std::string& signalName) const;
		float getFloatSignal(const std::string& signalName) const;
		std::string getStringSignal(const std::string& signalName) const;

		int getObjectHandle(const std::string& objectName) const;
		Pose getObjectPose(int objectHandle) const;
		Position getObjectPosition(int objectHandle) const;
		Orientation getObjectOrientation(int objectHandle) const;

		void setLogMode(LogMode mode);
		void log_msg(const std::string& message) const;

		~CoppeliaSimClient();
	};
}

