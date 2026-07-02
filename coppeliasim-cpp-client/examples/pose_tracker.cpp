#include "coppeliasim-cpp-client.h"

#include <thread>
#include <chrono>


int main()
{
	auto client = coppeliasim_cpp::CoppeliaSimClient::connect(
		"127.0.0.1", 19999, coppeliasim_cpp::LogMode::LOG_CMD);
	if (!client)
	{
		std::cerr << "Failed to connect to CoppeliaSim." << '\n';
		return 1;
	}

	client->logMsg("You can log info to the Command line and CoppeliaSim!");

	if (!client->startSimulation())
	{
		std::cerr << "Failed to start the simulation." << '\n';
		return 1;
	}

	const std::optional<int> objHandle = client->getObjectHandle("Cuboid");
	if (!objHandle)
	{
		std::cerr << "Object 'Cuboid' not found." << '\n';
		return 1;
	}

	while (client->isConnected())
	{
		const std::optional<coppeliasim_cpp::Pose> pose = client->getObjectPose(*objHandle);
		if (pose)
		{
			std::cout << "Object position: " << pose->position.x << ", "
				<< pose->position.y << ", " << pose->position.z << '\n';
			std::cout << "Object orientation: " << pose->orientation.alpha << ", "
				<< pose->orientation.beta << ", " << pose->orientation.gamma << '\n';
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}
