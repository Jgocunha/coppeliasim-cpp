#include "client.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

namespace coppeliasim_cpp
{

	CoppeliaSimClient::CoppeliaSimClient(const std::string& address, const int port, LogMode mode)
		: connectionPort(port), logMode(mode),
		connectionAddress(std::make_unique<simxChar[]>(address.length() + 1)) // NOLINT(modernize-avoid-c-arrays) -- C string buffer for the C API.
	{
		std::ranges::copy(address, connectionAddress.get());
		connectionAddress[address.length()] = '\0'; // Null-terminate the string
	}

	CoppeliaSimClient::CoppeliaSimClient(CoppeliaSimClient&& other) noexcept
		: clientID(std::exchange(other.clientID, -1)),
		connectionPort(other.connectionPort),
		logMode(other.logMode),
		connectionAddress(std::move(other.connectionAddress))
	{
	}

	CoppeliaSimClient& CoppeliaSimClient::operator=(CoppeliaSimClient&& other) noexcept
	{
		if (this != &other)
		{
			if (clientID != -1)
			{
				simxFinish(clientID); // release our current handle before taking the other's
			}
			clientID = std::exchange(other.clientID, -1);
			connectionPort = other.connectionPort;
			logMode = other.logMode;
			connectionAddress = std::move(other.connectionAddress);
		}
		return *this;
	}

	CoppeliaSimClient::~CoppeliaSimClient()
	{
		simxFinish(clientID); // tolerates clientID == -1 (no-op when unconnected/moved-from)
	}

	std::optional<CoppeliaSimClient> CoppeliaSimClient::connect(
		const std::string& address, int port, LogMode mode)
	{
		CoppeliaSimClient client(address, port, mode);
		if (!client.initialize())
		{
			return std::nullopt;
		}
		return client;
	}

	bool CoppeliaSimClient::initialize()
	{
		constexpr simxUChar waitUntilConnected = 1;
		constexpr simxUChar doNotReconnectOnceDisconnected = 1;
		constexpr simxInt timeoutInMs = 2000;
		constexpr simxInt commThreadCycleInMs = 5;
		clientID = simxStart(connectionAddress.get(), connectionPort,
			waitUntilConnected, doNotReconnectOnceDisconnected, timeoutInMs, commThreadCycleInMs);

		if (clientID == -1)
		{
			std::cout << "Failed to connect to CoppeliaSim.\n";
			return false;
		}

		logMsg("Connected to CoppeliaSim successfully!");

		return true;
	}

	bool CoppeliaSimClient::isConnected() const
	{
		// A negative handle is never connected; calling the C API with it would
		// index its connection arrays out of bounds.
		if (clientID < 0)
		{
			return false;
		}
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

	bool CoppeliaSimClient::startSimulation() const
	{
		const simxInt rc = simxStartSimulation(clientID, simx_opmode_blocking);
		if (rc != simx_return_ok)
		{
			return false;
		}
		logMsg("Simulation started.");
		return true;
	}

	bool CoppeliaSimClient::stopSimulation() const
	{
		const simxInt rc = simxStopSimulation(clientID, simx_opmode_blocking);
		if (rc != simx_return_ok)
		{
			return false;
		}
		logMsg("Simulation stopped.");
		return true;
	}

	void CoppeliaSimClient::setLogMode(LogMode mode)
	{
		logMode = mode;
	}

	bool CoppeliaSimClient::setIntegerSignal(const std::string& signalName, int signalValue) const
	{
		const simxInt rc = simxSetIntegerSignal(clientID, signalName.c_str(), signalValue, simx_opmode_oneshot);
		if (rc != simx_return_ok)
		{
			return false;
		}
		logMsg("Signal: " + signalName + " set to: " + std::to_string(signalValue));
		return true;
	}

	bool CoppeliaSimClient::setFloatSignal(const std::string& signalName, float signalValue) const
	{
		const simxInt rc = simxSetFloatSignal(clientID, signalName.c_str(), signalValue, simx_opmode_oneshot);
		if (rc != simx_return_ok)
		{
			return false;
		}
		logMsg("Signal: " + signalName + " set to: " + std::to_string(signalValue));
		return true;
	}

	bool CoppeliaSimClient::setStringSignal(const std::string& signalName, const std::string& signalValue) const
	{
		const auto *const signalData = reinterpret_cast<const simxUChar*>(signalValue.c_str());
		const auto signalLength = static_cast<simxInt>(signalValue.size());
		const simxInt rc = simxSetStringSignal(clientID, signalName.c_str(), signalData, signalLength, simx_opmode_blocking);
		if (rc != simx_return_ok)
		{
			return false;
		}
		logMsg("Signal: " + signalName + " set to: " + signalValue);
		return true;
	}

	std::optional<int> CoppeliaSimClient::getIntegerSignal(const std::string& signalName) const
	{
		simxInt signalValue = 0;
		const simxInt rc = simxGetIntegerSignal(clientID, signalName.c_str(), &signalValue, simx_opmode_blocking);
		if (rc != simx_return_ok)
		{
			return std::nullopt;
		}
		logMsg("Signal: " + signalName + " read as: " + std::to_string(signalValue));
		return signalValue;
	}

	std::optional<float> CoppeliaSimClient::getFloatSignal(const std::string& signalName) const
	{
		simxFloat signalValue = 0.0F;
		const simxInt rc = simxGetFloatSignal(clientID, signalName.c_str(), &signalValue, simx_opmode_blocking);
		if (rc != simx_return_ok)
		{
			return std::nullopt;
		}
		logMsg("Signal: " + signalName + " read as: " + std::to_string(signalValue));
		return signalValue;
	}

	std::optional<std::string> CoppeliaSimClient::getStringSignal(const std::string& signalName) const
	{
		simxInt signalLength = 0;
		simxUChar* signalValue = nullptr;
		const simxInt rc = simxGetStringSignal(clientID, signalName.c_str(), &signalValue, &signalLength, simx_opmode_blocking);
		// Guard the memory invariant the std::string constructor cannot verify:
		// only build the string when the call succeeded and gave us a valid buffer.
		if (rc != simx_return_ok || signalValue == nullptr || signalLength < 0)
		{
			return std::nullopt;
		}
		std::string result(reinterpret_cast<char*>(signalValue), signalLength);
		logMsg("Signal: " + signalName + " read as: " + result);
		return result;
	}

	std::optional<int> CoppeliaSimClient::getObjectHandle(const std::string& objectName) const
	{
		simxInt objectHandle = -1;
		const simxInt rc = simxGetObjectHandle(clientID, objectName.c_str(), &objectHandle, simx_opmode_blocking);
		if (rc != simx_return_ok)
		{
			return std::nullopt;
		}
		return objectHandle;
	}

	std::optional<Pose> CoppeliaSimClient::getObjectPose(int objectHandle) const
	{
		const std::optional<Position> position = getObjectPosition(objectHandle);
		const std::optional<Orientation> orientation = getObjectOrientation(objectHandle);
		if (!position || !orientation)
		{
			return std::nullopt;
		}
		return Pose{*position, *orientation};
	}

	std::optional<Position> CoppeliaSimClient::getObjectPosition(int objectHandle) const
	{
		std::array<simxFloat, 3> position{};
		const simxInt rc = simxGetObjectPosition(clientID, objectHandle, kWorldFrame, position.data(), simx_opmode_blocking);
		if (rc != simx_return_ok)
		{
			return std::nullopt;
		}
		return Position{position[0], position[1], position[2]};
	}

	std::optional<Orientation> CoppeliaSimClient::getObjectOrientation(int objectHandle) const
	{
		std::array<simxFloat, 3> orientation{};
		const simxInt rc = simxGetObjectOrientation(clientID, objectHandle, kWorldFrame, orientation.data(), simx_opmode_blocking);
		if (rc != simx_return_ok)
		{
			return std::nullopt;
		}
		return Orientation{orientation[0], orientation[1], orientation[2]};
	}

	void CoppeliaSimClient::logMsg(const std::string& message) const
	{
		switch (logMode)
		{
		case LogMode::LOG_CMD:
			std::cout << message << '\n';
			break;
		case LogMode::LOG_COPPELIA:
			if (clientID != -1)  // Ensure we're connected before trying to log to CoppeliaSim
			{
				simxAddStatusbarMessage(clientID, message.c_str(), simx_opmode_oneshot);
			}
			break;
		case LogMode::LOG_COPPELIA_CMD:
			std::cout << message << '\n';
			if (clientID != -1)  // Ensure we're connected before trying to log to CoppeliaSim
			{
				simxAddStatusbarMessage(clientID, message.c_str(), simx_opmode_oneshot);
			}
			break;
		case LogMode::NO_LOGS:
		default:
			// Do nothing
			break;
		}
	}
}
