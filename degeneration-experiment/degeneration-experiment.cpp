// degeneration-experiment.cpp : Defines the entry point for the application.
//

#include "degeneration-experiment.h"

#include <random>

int main()
{
    int clientID;

    // Connect to CoppeliaSim
    clientID = simxStart((simxChar*)"127.0.0.1", 19999, true, true, 2000, 5);

    // Check if the connection was successful
    if (clientID == -1)
    {
        printf("Failed to connect to CoppeliaSim.\n");
        return 1;
    }
    else
    {
        printf("Connected to CoppeliaSim successfully!\n");

        // Start the simulation
        simxStartSimulation(clientID, simx_opmode_blocking);

        static int numBoxes = 10;
        for (int i = 0; i < numBoxes; i++)
        {
            // Send a signal to create the shape
            simxSetIntegerSignal(clientID, "createShapeSignal", 1, simx_opmode_blocking);

            // Wait for the signal to be processed and receive the box handle
            simxInt boxHandle;
            std::string cuboidName = "Cuboid_" + std::to_string(i);
            printf("%s", cuboidName.c_str());
            simxGetObjectHandle(clientID, cuboidName.c_str(), &boxHandle, simx_opmode_blocking);
            //simxSetInt32Signal(clientID, "boxHandleSignal", &boxHandle, simx_opmode_blocking);

            // Check if the box handle was received successfully
            if (boxHandle != -1)
            {
                printf("Box created with handle: %d\n", boxHandle);

                simxInt signalLength;
                simxUChar* signalValue;
                simxGetAndClearStringSignal(clientID, "shapeColorSignal", &signalValue, &signalLength, simx_opmode_blocking);

                printf("Received signal value: ");
                for (int j = 0; j < signalLength; j++)
                {
                    printf("%c", signalValue[j]);
                }
                printf("\n");

                Sleep(1000);

                // Remove the box from the scene
                //simxRemoveObject(clientID, boxHandle, simx_opmode_blocking);
            }
            else
            {
                printf("Failed to create the box in CoppeliaSim.\n");
            }
        }

        // Stop the simulation
        simxStopSimulation(clientID, simx_opmode_blocking);
    }

    // Close the connection with CoppeliaSim
    simxFinish(clientID);
    return 0;
}
