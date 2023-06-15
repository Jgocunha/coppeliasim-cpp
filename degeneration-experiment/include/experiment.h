
#pragma once

// define signals here.
#define CREATE_SHAPE_SIGNAL "createShapeSignal"
#define SHAPE_COLOR_SIGNAL "shapeColorSignal"
#define PICK_UP_SHAPE_SIGNAL "pickUpShapeSignal"
#define PLACE_SHAPE_SIGNAL "placeShapeSignal"

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
	void setupSignals();
	void createShape();
	void getShapeParameters();
	void pickUpShape();
	void placeShape();
	void computeTargetBox();
};