#include "./experiment.h"

DegenerationExperiment::DegenerationExperiment(const int& trials)
	:trials(trials)
{
}

bool DegenerationExperiment::initialize()
{
	if (client.initialize())
	{
		setupSignals();
		return true;
	}
	return false;
}

void DegenerationExperiment::setupSignals()
{
	simxSetIntegerSignal(client.getClientID(), CREATE_SHAPE_SIGNAL, 0, simx_opmode_blocking);
	simxSetIntegerSignal(client.getClientID(), PICK_UP_SHAPE_SIGNAL, 0, simx_opmode_blocking);
	simxSetIntegerSignal(client.getClientID(), PLACE_SHAPE_SIGNAL, 0, simx_opmode_blocking);

	const char* signalValue = "UNDEFINED";
	const simxUChar* signalData = reinterpret_cast<const simxUChar*>(signalValue);
	simxInt signalLength = static_cast<simxInt>(strlen(signalValue));

	simxSetStringSignal(client.getClientID(), SHAPE_COLOR_SIGNAL, signalData, signalLength, simx_opmode_blocking);

	client.log("All signals were initialized.");
}

void DegenerationExperiment::run()
{
	int currentTrial = 1;

	while (currentTrial <= trials)
	{
		// create shape
		createShape();

		// read shape color
		cuboid.name = "Cuboid_" + std::to_string(currentTrial);
		getShapeParameters();
		
		// compute what is the target box
		computeTargetBox();

		// go pick shape
		pickUpShape();

		// go place shape
		placeShape();

		// go to home position

		Sleep(2000);

		currentTrial++;
	}
}

void DegenerationExperiment::stop()
{
	simxStopSimulation(client.getClientID(), simx_opmode_blocking);
	client.log("Stopped simulation.");
}

void DegenerationExperiment::createShape()
{
	simxSetIntegerSignal(client.getClientID(), CREATE_SHAPE_SIGNAL, 1, simx_opmode_blocking);

	client.log("CREATE_SHAPE_SIGNAL sent to CoppeliaSim.");
}

void DegenerationExperiment::getShapeParameters()
{
	simxGetObjectHandle(client.getClientID(), cuboid.name.c_str(), &cuboid.handle, simx_opmode_blocking);

	simxInt signalLength;
	simxUChar* signalValue;
	simxGetAndClearStringSignal(client.getClientID(), SHAPE_COLOR_SIGNAL, &signalValue, &signalLength, simx_opmode_blocking);
	cuboid.color = std::string(reinterpret_cast<char*>(signalValue), signalLength);

	client.log("Cuboid created with handle: " + std::to_string(cuboid.handle) + " and color " + cuboid.color);
}

void DegenerationExperiment::pickUpShape()
{
	simxSetIntegerSignal(client.getClientID(), PICK_UP_SHAPE_SIGNAL, 1, simx_opmode_oneshot);

	client.log("Sent PICK_UP_SHAPE_SIGNAL to CoppeliaSim.");
}

void DegenerationExperiment::placeShape()
{
	simxSetIntegerSignal(client.getClientID(), PLACE_SHAPE_SIGNAL, box, simx_opmode_oneshot);

	client.log("Sent PLACE_SHAPE_SIGNAL to CoppeliaSim.");
}

void DegenerationExperiment::computeTargetBox()
{
	std::string color = cuboid.color;

	if (color == "RED")
	{
		box = BoxToPlaceShape::BOX_1;
		client.log("Target box is BOX_1");
	}
	else if (color == "ORANGE")
	{
		box = BoxToPlaceShape::BOX_2;
		client.log("Target box is BOX_2");
	}
	else if (color == "YELLOW")
	{
		box = BoxToPlaceShape::BOX_3;
		client.log("Target box is BOX_3");
	}
	else if (color == "GREEN")
	{
		box = BoxToPlaceShape::BOX_4;
		client.log("Target box is BOX_4");
	}
	else if (color == "BLUE")
	{
		box = BoxToPlaceShape::BOX_5;
		client.log("Target box is BOX_5");
	}
	else if (color == "INDIGO")
	{
		box = BoxToPlaceShape::BOX_6;
		client.log("Target box is BOX_6");
	}
	else if (color == "VIOLET")
	{
		box = BoxToPlaceShape::BOX_7;
		client.log("Target box is BOX_7");
	}
	else
	{
		box = BoxToPlaceShape::BOX_1; // Default to BOX_1 if the color is unknown
		client.log("Unknown color. Target box set to BOX_1");
	}
}
