
#pragma once

#include "./client.h"

struct Shape
{
	std::string name;
	simxInt handle;
	std::string color;
};


class DegenerationExperiment
{
private:
	CoppeliaSimClient client;
	Shape cuboid;
	int trials;

public:
	DegenerationExperiment(const int& trials);

	bool start();
	void run();
	void stop();

private:
	void createCuboid();
	void getCuboidParameters();
	void pickUpCuboid();
};