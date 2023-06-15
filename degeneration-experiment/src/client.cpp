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

	log("Connected to CoppeliaSim successfully!");

	return true;
}

int CoppeliaSimClient::getClientID()
{
	return clientID;
}

void CoppeliaSimClient::startSimulation()
{
	simxStartSimulation(clientID, simx_opmode_blocking);
}

void CoppeliaSimClient::stopSimulation()
{
	simxStopSimulation(clientID, simx_opmode_blocking);
}

void CoppeliaSimClient::log(const std::string& message)
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