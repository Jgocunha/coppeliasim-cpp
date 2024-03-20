#include "coppeliasim-cpp-client.h"


int main()
{
	coppeliasim_cpp::CoppeliaSimClient client;

	if (client.initialize())
	{
		client.log_msg("You can log info to the Command line and CoppeliaSim!");

		client.startSimulation();
		client.log_msg("Simulation started.");
		const int obj_handle = client.getObjectHandle("Cuboid");

		while(client.isConnected())
		{
			const coppeliasim_cpp::Pose obj_pose = client.getObjectPose(obj_handle);
			std::cout << "Object position: " << obj_pose.position.x << ", " << obj_pose.position.y << ", " << obj_pose.position.z << std::endl;
			std::cout << "Object orientation: " << obj_pose.orientation.alpha << ", " << obj_pose.orientation.beta << ", " << obj_pose.orientation.gamma << std::endl;

			const coppeliasim_cpp::Position obj_pos = client.getObjectPosition(obj_handle);
			std::cout << "Object position: " << obj_pos.x << ", " << obj_pos.y << ", " << obj_pos.z << std::endl;

			const coppeliasim_cpp::Orientation obj_ori = client.getObjectOrientation(obj_handle);
			std::cout << "Object orientation: " << obj_ori.alpha << ", " << obj_ori.beta << ", " << obj_ori.gamma << std::endl;
			
			Sleep(100);
		}
	}
	else
	{
		return 1;
	}

	return 0;
}
