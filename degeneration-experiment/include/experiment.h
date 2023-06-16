
#pragma once

// define signals here.
#define CREATE_SHAPE_SIGNAL "createShape"
#define SHAPE_CREATED_SIGNAL "shapeCreated"

#define GRASP_SHAPE_SIGNAL "graspShape"
#define SHAPE_GRASPED_SIGNAL "shapeGrasped"

#define PLACE_SHAPE_SIGNAL "placeShape"
#define SHAPE_PLACED_SIGNAL "shapePlaced"

#define SHAPE_COLOR_SIGNAL "shapeColor"
#define SHAPE_BOX_SIGNAL "shapeBox"

#include <map>

#include "./client.h"

struct Shape
{
	std::string name;
	simxInt handle;
	std::string color;
};

enum BoxToPlaceShape
{
	BOX_1 = 1, // red
	BOX_2, // orange
	BOX_3, // yellow
	BOX_4, // green
	BOX_5, // blue
	BOX_6, // indigo
	BOX_7, // violet
};

extern std::map<BoxToPlaceShape, std::string> boxToPlaceShapeMap;

class DegenerationExperiment
{
private:
	CoppeliaSimClient client;
	Shape cuboid;
	int trials;
	BoxToPlaceShape box;

public:
	DegenerationExperiment(const int& trials);

	bool initialize();
	void run();
	void stop();

private:
	void resetSignals();
	void createShape();
	void getShapeParameters();
	void pickUpShape();
	void placeShape();
	void computeTargetBox();
};