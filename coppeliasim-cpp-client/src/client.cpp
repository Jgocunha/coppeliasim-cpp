#include "./client.h"

CoppeliaSimClient::CoppeliaSimClient(const std::string& connectionAddress, const int& connectionPort)
	: clientID(-1), connectionPort(connectionPort)
{
	// Allocate memory for the connection address
	this->connectionAddress = new simxChar[connectionAddress.size() + 1];
	strcpy(this->connectionAddress, connectionAddress.c_str());
}

bool CoppeliaSimClient::initialize()
{
	// Connect to CoppeliaSim
	clientID = simxStart(connectionAddress, connectionPort, true, true, 2000, 5);

	// Check if the connection was successful
	if (clientID == -1)
	{
		printf("Failed to connect to CoppeliaSim.\n");
		return false;
	}

	log_msg("Connected to CoppeliaSim successfully!");

	return true;
}

int CoppeliaSimClient::getClientID()
{
	return clientID;
}

void CoppeliaSimClient::startSimulation()
{
	simxStartSimulation(clientID, simx_opmode_blocking);
	log_msg("Simulation started.");
}

void CoppeliaSimClient::stopSimulation()
{
	simxStopSimulation(clientID, simx_opmode_blocking);
	log_msg("Simulation stopped.");
}

void CoppeliaSimClient::setIntegerSignal(const std::string& signalName, const int& signalValue)
{
	simxSetIntegerSignal(clientID, signalName.c_str(), signalValue, simx_opmode_oneshot);
	log_msg("Signal: " + signalName + " set to: " + std::to_string(signalValue));
}

void CoppeliaSimClient::setStringSignal(const std::string& signalName, const std::string& signalValue)
{
	const simxUChar* signalData = reinterpret_cast<const simxUChar*>(signalValue.c_str());
	simxInt signalLength = static_cast<simxInt>(strlen(signalValue.c_str()));
	simxSetStringSignal(clientID, signalName.c_str(), signalData, signalLength, simx_opmode_blocking);
	log_msg("Signal: " + signalName + " set to: " + signalValue);
}

void CoppeliaSimClient::setFloatSignal(const std::string& signalName, const double& signalValue)
{
	simxSetFloatSignal(clientID, signalName.c_str(), signalValue, simx_opmode_oneshot);
	log_msg("Signal: " + signalName + " set to: " + std::to_string(signalValue));
}

int CoppeliaSimClient::getIntegerSignal(const std::string& signalName)
{
	simxInt signalValue;
	simxGetIntegerSignal(clientID, signalName.c_str(), &signalValue, simx_opmode_blocking);
	//setIntegerSignal(signalName.c_str(), 0);
	log_msg("Signal: " + signalName + " read as: " + std::to_string(signalValue));
	return signalValue;
}

std::string CoppeliaSimClient::getStringSignal(const std::string& signalName)
{
	simxInt signalLength;
	simxUChar* signalValue;
	std::string internalSignalValue;
	simxGetAndClearStringSignal(clientID, signalName.c_str(), &signalValue, &signalLength, simx_opmode_blocking);
	
	internalSignalValue = std::string(reinterpret_cast<char*>(signalValue), signalLength);
	log_msg("Signal: " + signalName + " read as: " + internalSignalValue);
	return internalSignalValue;
}

double CoppeliaSimClient::getFloatSignal(const std::string& signalName)
{
	simxFloat signalValue;
	simxGetFloatSignal(clientID, signalName.c_str(), &signalValue, simx_opmode_blocking);
	//setIntegerSignal(signalName.c_str(), 0);
	log_msg("Signal: " + signalName + " read as: " + std::to_string(signalValue));
	return signalValue;
}

void CoppeliaSimClient::log_msg(const std::string& message) const
{
	// Log to the console
	if (LOG_ON_CMD)
		printf("%s\n", message.c_str());

	// Log to CoppeliaSim's status bar
	if (LOG_ON_COPPELIA)
		simxAddStatusbarMessage(clientID, message.c_str(), simx_opmode_oneshot);
}

CoppeliaSimClient::~CoppeliaSimClient()
{
	// Cleanup resources
	simxFinish(clientID);
	// Deallocate the connection address memory
	delete[] connectionAddress;
}