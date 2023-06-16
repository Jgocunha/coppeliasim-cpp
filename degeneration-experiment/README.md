# Project: Degeneration Experiment

This project aims to simulate a robot placing colored boxes into the appropriate division of a box using the CoppeliaSim simulator. The communication between the simulation and the main executable is done via signals.

## File Structure

The project has the following file structure:

- libs/
  - coppeliasim/
    - extApi.c
    - extApiPlatform.c
- include/
  - client.h
  - experiment.h
- src/
  - client.cpp
  - experiment.cpp
  - logger.cpp [NOT IMPLEMENTED]
- degeneration-experiment.cpp


## File Descriptions

Here's a description of each file in the project:

- `client.h` and `client.cpp`: These files define and implement the `CoppeliaSimClient` class. This class encapsulates the communication with CoppeliaSim. It provides methods for initializing the connection, starting and stopping the simulation, setting and getting signal values, and logging messages to the console and the simulator's status bar.

- `experiment.h` and `experiment.cpp`: These files define and implement the `DegenerationExperiment` class. This class represents the logic of the experiment, including creating shapes, getting shape parameters, picking up and placing shapes, computing the target box, and running the experiment for a specified number of trials. The `DegenerationExperiment` class uses an instance of `CoppeliaSimClient` to communicate with the simulator.

- `degeneration-experiment.cpp`: This is the main executable file that runs the experiment. It creates an instance of `DegenerationExperiment`, initializes the experiment, runs the experiment for a specified number of trials, and stops the experiment. The `main` function acts as the entry point of the program.


## Using the `CoppeliaSimClient` Class

The `CoppeliaSimClient` class is a versatile class that provides a convenient interface for communicating with CoppeliaSim. It can be reused across different projects that require interaction with the simulator. To use the `CoppeliaSimClient` class in your project, follow these steps:

1. Include the `client.h` header file in your source files that need to interact with CoppeliaSim.

2. Create an instance of the `CoppeliaSimClient` class by providing the connection address and port number to the constructor.

3. Initialize the client by calling the `initialize` method. This establishes a connection with CoppeliaSim.

4. Use the various methods of the `CoppeliaSimClient` class to perform actions in the simulator, such as starting and stopping the simulation, setting and getting signal values, and logging messages.

5. Clean up resources by destroying the `CoppeliaSimClient` object when it is no longer needed. This will automatically disconnect from CoppeliaSim.

You can refer to the `main.cpp` file in this project as an example of how to use the `CoppeliaSimClient` class in conjunction with the `DegenerationExperiment` class to run the experiment and interact with the CoppeliaSim simulator.

Feel free to modify and extend the project to suit your specific requirements.
