#include "client.h"

namespace coppeliasim_cpp
{

	CoppeliaSimClient::CoppeliaSimClient(const std::string& address, const int port, LogMode mode)
		: clientID(-1), connectionPort(port), logMode(mode),
		connectionAddress(std::make_unique<simxChar[]>(address.length() + 1))
	{
		// Use std::ranges::copy to copy the string to the allocated array
		std::ranges::copy(address, connectionAddress.get());
		connectionAddress[address.length()] = '\0'; // Null-terminate the string
	}

	bool CoppeliaSimClient::initialize()
	{
		clientID = simxStart(connectionAddress.get(), connectionPort, true, true, 2000, 5);

		if (clientID == -1)
		{
			std::cout << "Failed to connect to CoppeliaSim.\n";
			return false;
		}

		log_msg("Connected to CoppeliaSim successfully!");

		return true;
	}

	bool CoppeliaSimClient::isConnected() const
	{
		const int connectionState = simxGetConnectionId(clientID);
		if (connectionState == -1)
		{
			std::cout << "Connection to CoppeliaSim lost.\n";
			return false;
		}
		return true;
	}

	int CoppeliaSimClient::getClientID() const
	{
		return clientID;
	}

	void CoppeliaSimClient::startSimulation() const
	{
		simxStartSimulation(clientID, simx_opmode_blocking);
		log_msg("Simulation started.");
	}

	void CoppeliaSimClient::stopSimulation() const
	{
		simxStopSimulation(clientID, simx_opmode_blocking);
		log_msg("Simulation stopped.");
	}

	void CoppeliaSimClient::setLogMode(LogMode mode)
	{
		logMode = mode;
	}

	void CoppeliaSimClient::setIntegerSignal(const std::string& signalName, int signalValue) const
	{
		simxSetIntegerSignal(clientID, signalName.c_str(), signalValue, simx_opmode_oneshot);
		log_msg("Signal: " + signalName + " set to: " + std::to_string(signalValue));
	}

	void CoppeliaSimClient::setStringSignal(const std::string& signalName, const std::string& signalValue) const
	{
		const auto signalData = reinterpret_cast<const simxUChar*>(signalValue.c_str());
		const auto signalLength = static_cast<simxInt>(strlen(signalValue.c_str()));
		simxSetStringSignal(clientID, signalName.c_str(), signalData, signalLength, simx_opmode_blocking);
		log_msg("Signal: " + signalName + " set to: " + signalValue);
	}

	void CoppeliaSimClient::setFloatSignal(const std::string& signalName, const float& signalValue) const
	{
		simxSetFloatSignal(clientID, signalName.c_str(), signalValue, simx_opmode_oneshot);
		log_msg("Signal: " + signalName + " set to: " + std::to_string(signalValue));
	}

	int CoppeliaSimClient::getIntegerSignal(const std::string& signalName) const
	{
		simxInt signalValue;
		simxGetIntegerSignal(clientID, signalName.c_str(), &signalValue, simx_opmode_blocking);
		log_msg("Signal: " + signalName + " read as: " + std::to_string(signalValue));
		return signalValue;
	}

	std::string CoppeliaSimClient::getStringSignal(const std::string& signalName) const
	{
		simxInt signalLength;
		simxUChar* signalValue;
		simxGetStringSignal(clientID, signalName.c_str(), &signalValue, &signalLength, simx_opmode_blocking);

		std::string internalSignalValue = std::string(reinterpret_cast<char*>(signalValue), signalLength);
		log_msg("Signal: " + signalName + " read as: " + internalSignalValue);
		return internalSignalValue;
	}

	int CoppeliaSimClient::getObjectHandle(const std::string& objectName) const
	{
		simxInt objectHandle;
		simxGetObjectHandle(clientID, objectName.c_str(), &objectHandle, simx_opmode_blocking);
		return objectHandle;
	}

	Pose CoppeliaSimClient::getObjectPose(int objectHandle) const
	{
		const Position position = getObjectPosition(objectHandle);
		const Orientation orientation = getObjectOrientation(objectHandle);
		return { position, orientation };
	}

	Position CoppeliaSimClient::getObjectPosition(int objectHandle) const
	{
		simxFloat position[3];
		simxGetObjectPosition(clientID, objectHandle, -1, position, simx_opmode_blocking);
		return { position[0], position[1], position[2] };
	}

	Orientation CoppeliaSimClient::getObjectOrientation(int objectHandle) const
	{
		simxFloat orientation[3];
		simxGetObjectOrientation(clientID, objectHandle, -1, orientation, simx_opmode_blocking);
		return { orientation[0], orientation[1], orientation[2] };
	}

	float CoppeliaSimClient::getFloatSignal(const std::string& signalName) const
	{
		simxFloat signalValue;
		simxGetFloatSignal(clientID, signalName.c_str(), &signalValue, simx_opmode_blocking);
		log_msg("Signal: " + signalName + " read as: " + std::to_string(signalValue));
		return signalValue;
	}

	void CoppeliaSimClient::log_msg(const std::string& message) const
	{
		switch (logMode)
		{
		case LogMode::LOG_CMD:
			std::cout << message << std::endl;
			break;
		case LogMode::LOG_COPPELIA:
			if (clientID != -1)  // Ensure we're connected before trying to log to CoppeliaSim
				simxAddStatusbarMessage(clientID, message.c_str(), simx_opmode_oneshot);
			break;
		case LogMode::LOG_COPPELIA_CMD:
			std::cout << message << std::endl;
			if (clientID != -1)  // Ensure we're connected before trying to log to CoppeliaSim
				simxAddStatusbarMessage(clientID, message.c_str(), simx_opmode_oneshot);
			break;
		case LogMode::NO_LOGS:
		default:
			// Do nothing
			break;
		}
	}

	CoppeliaSimClient::~CoppeliaSimClient()
	{
		simxFinish(clientID);
	}
}
