

#include "coppeliasim-cpp-client.h"


int main()
{
	CoppeliaSimClient client;

	if (client.initialize())
	{
		client.log("You can log info to the Command line and CoppeliaSim!");
	}
	else
	{
		return 1;
	}

	return 0;
}
