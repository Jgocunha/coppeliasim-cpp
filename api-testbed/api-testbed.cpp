// api-testbed.cpp : Defines the entry point for the application.
//

#include "api-testbed.h"

using namespace std;

int main()
{
	int clientID;

	// Connect to CoppeliaSim
	clientID = simxStart((simxChar*)"127.0.0.1", 19999, true, true, 2000, 5);

	simxInt pingTime;

	// Check if the connection was successful
	if (clientID == -1)
	{
		printf("Failed to connect to CoppeliaSim.\n");
		return 1;
	}
	else
	{
		printf("Connected to CoppeliaSim successfully!\n");

		// Retrieve the objects in the scene
		simxInt objectCount;
		simxInt* objectHandles;
		simxGetObjects(clientID, sim_handle_all, &objectCount, &objectHandles, simx_opmode_blocking);

		printf("Number of objects in the scene: %d\n", objectCount);

		// Retrieve the mouse position 
		double startTime = simxGetLastCmdTime(clientID);
		double maxTime = 100000.0;
		while (simxGetLastCmdTime(clientID) - startTime < maxTime)
		{
			int mouseX;
			simxGetIntegerParameter(clientID, sim_intparam_mouse_x, &mouseX, simx_opmode_streaming);
			printf("Mouse position x: %d\n", mouseX);

			// Delay for a short period
			Sleep(10);
		}

		// Send a status message to CoppeliaSim
		simxAddStatusbarMessage(clientID, "Hello CoppeliaSim!", simx_opmode_oneshot);

		// Make sure the last command has arrived
		simxGetPingTime(clientID, &pingTime);
	}

	// Close the connection with CoppeliaSim
	simxFinish(clientID);

	return 0;
}
