#include "./experiment.h"

// Define and initialize the map
std::map<BoxToPlaceShape, std::string> boxToPlaceShapeMap = {
	{BoxToPlaceShape::BOX_1, "BOX_1"},
	{BoxToPlaceShape::BOX_2, "BOX_2"},
	{BoxToPlaceShape::BOX_3, "BOX_3"},
	{BoxToPlaceShape::BOX_4, "BOX_4"},
	{BoxToPlaceShape::BOX_5, "BOX_5"},
	{BoxToPlaceShape::BOX_6, "BOX_6"},
	{BoxToPlaceShape::BOX_7, "BOX_7"}
};

DegenerationExperiment::DegenerationExperiment(const int& trials)
	:trials(trials)
{
}

bool DegenerationExperiment::initialize()
{
	if (client.initialize())
	{
		resetSignals();
		return true;
	}
	return false;
}

void DegenerationExperiment::resetSignals()
{
	client.setIntegerSignal(CREATE_SHAPE_SIGNAL, 0);
	client.setIntegerSignal(SHAPE_CREATED_SIGNAL, 0);
	client.setIntegerSignal(GRASP_SHAPE_SIGNAL, 0);
	client.setIntegerSignal(SHAPE_GRASPED_SIGNAL, 0);
	client.setIntegerSignal(PLACE_SHAPE_SIGNAL, 0);
	client.setIntegerSignal(SHAPE_PLACED_SIGNAL, 0);

	client.setStringSignal(SHAPE_COLOR_SIGNAL, "UNDEFINED");
	client.setStringSignal(SHAPE_BOX_SIGNAL, "UNDEFINED");

	client.log("All signals were reset.");
}

void DegenerationExperiment::run()
{
	int currentTrial = 1;

	while (currentTrial <= trials)
	{
		createShape();

		cuboid.name = "Cuboid_" + std::to_string(currentTrial);
		getShapeParameters();
		
		computeTargetBox();

		pickUpShape();

		placeShape();

		Sleep(2000);

		resetSignals();
		currentTrial++;
	}
}

void DegenerationExperiment::stop()
{
	client.stopSimulation();
}

void DegenerationExperiment::createShape()
{
	client.setIntegerSignal(CREATE_SHAPE_SIGNAL, 1);

	int wasShapeCreated = 0;
	do
	{
		wasShapeCreated = client.getIntegerSignal(SHAPE_CREATED_SIGNAL);
		Sleep(100);
	} while (!wasShapeCreated);
}

void DegenerationExperiment::getShapeParameters()
{
	simxGetObjectHandle(client.getClientID(), cuboid.name.c_str(), &cuboid.handle, simx_opmode_blocking);

	cuboid.color = client.getStringSignal(SHAPE_COLOR_SIGNAL);
}

void DegenerationExperiment::pickUpShape()
{
	client.setIntegerSignal(GRASP_SHAPE_SIGNAL, 1);

	int wasShapeGrasped = 0;
	do
	{
		wasShapeGrasped = client.getIntegerSignal(SHAPE_GRASPED_SIGNAL);
		Sleep(100);
	} while (!wasShapeGrasped);
}

void DegenerationExperiment::placeShape()
{
	client.setIntegerSignal(PLACE_SHAPE_SIGNAL, 1);

	int wasShapePlaced = 0;
	do
	{
		wasShapePlaced = client.getIntegerSignal(SHAPE_PLACED_SIGNAL);
		Sleep(100);
	} while (!wasShapePlaced);
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

	client.setStringSignal(SHAPE_BOX_SIGNAL, boxToPlaceShapeMap[box]);
}
