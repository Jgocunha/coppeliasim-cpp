#include "./experiment.h"

DegenerationExperiment::DegenerationExperiment(const int& trials)
	:trials(trials)
{
}

bool DegenerationExperiment::start()
{
	return client.initialize();
}

void DegenerationExperiment::run()
{
	int currentTrial = 1;

	while (currentTrial <= trials)
	{
		// create shape
		createCuboid();

		// read shape color
		cuboid.name = "Cuboid_" + std::to_string(currentTrial-1);
		getCuboidParameters();

		// go pick shape
		// go place shape
		// go to home position

		Sleep(2000);

		currentTrial++;
	}
}

void DegenerationExperiment::stop()
{
	simxStopSimulation(client.getClientID(), simx_opmode_blocking);
}

void DegenerationExperiment::createCuboid()
{
	simxSetIntegerSignal(client.getClientID(), "createShapeSignal", 1, simx_opmode_blocking);
	client.log("createShapeSignal sent to CoppeliaSim.");
}

void DegenerationExperiment::getCuboidParameters()
{
	simxGetObjectHandle(client.getClientID(), cuboid.name.c_str(), &cuboid.handle, simx_opmode_blocking);
	client.log("Cuboid created with handle: " + std::to_string(cuboid.handle));

	simxInt signalLength;
	simxUChar* signalValue;
	simxGetAndClearStringSignal(client.getClientID(), "shapeColorSignal", &signalValue, &signalLength, simx_opmode_blocking);

	cuboid.color = std::string(reinterpret_cast<char*>(signalValue), signalLength);
	client.log("The color of the cuboid is:" + cuboid.color);
}

void DegenerationExperiment::pickUpCuboid()
{
}
