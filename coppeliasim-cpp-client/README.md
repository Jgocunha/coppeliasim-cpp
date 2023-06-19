# CoppeliaSim C++ Client

The CoppeliaSim C++ Client is a library that allows you to control and communicate with CoppeliaSim (formerly known as V-REP) from your C++ program. This client provides a convenient interface to interact with CoppeliaSim's simulation environment and exchange data using signals.

## Dependencies

To use the CoppeliaSim C++ Client, you need the following dependencies:

- CoppeliaSim: You should have a working installation of CoppeliaSim on your system. The client relies on the CoppeliaSim API to establish a connection and communicate with the simulation environment.

## Installation

To use the CoppeliaSim C++ Client, you need to follow these steps:

1. Download or clone the repository to your local machine.

2. Set up the necessary dependencies, including CoppeliaSim. Make sure you have the CoppeliaSim API and related files (`extApi.h` and `extApiPlatform.h`) available in your project.

3. Include the necessary directories and source files in your build system. If you are using CMake, you can use the provided CMakeLists.txt file as a starting point. Adjust it to match your project structure and dependencies.

4. Build your project using your preferred build system.

## Usage

To use the CoppeliaSim C++ Client in your project, follow these steps:

2. Create an instance of the CoppeliaSimClient class:

   ```cpp
   #include "coppeliasim-cpp-client.h"

   int main()
   {
       CoppeliaSimClient client;

       // ... rest of the code ...
   }
   ```

3. Initialize the client:
   
   ```cpp
   if (client.initialize())
    {
        // Initialization successful
    }
    else
    {
        // Initialization failed
    }
    ```

Initialize the client by calling the initialize() method. The initialize() method establishes a connection with CoppeliaSim. It returns true if the connection is successful and false otherwise.

## Usage

4. Use the available methods

Use the available methods of the CoppeliaSimClient class to control CoppeliaSim and exchange data. The available methods include:

- `startSimulation()`: Starts the simulation in CoppeliaSim.
- `stopSimulation()`: Stops the simulation in CoppeliaSim.
- `setIntegerSignal(const std::string& signalName, const int& signalValue)`: Sets an integer signal in CoppeliaSim with the specified name and value.
- `setStringSignal(const std::string& signalName, const std::string& signalValue)`: Sets a string signal in CoppeliaSim with the specified name and value.
- `getIntegerSignal(const std::string& signalName)`: Retrieves the value of an integer signal from CoppeliaSim with the specified name.
- `getStringSignal(const std::string& signalName)`: Retrieves the value of a string signal from CoppeliaSim with the specified name.
- `log(const std::string& message)`: Logs a message to the console and/or CoppeliaSim's status bar, depending on the logging settings.

Ensure to handle the return values of these methods and perform appropriate error checking.

5. Clean up resources

Clean up resources by destroying the CoppeliaSimClient instance. The destructor is automatically called at the end of the program.

### Logging

The CoppeliaSim C++ Client provides a logging mechanism to output messages. You can control where the messages are logged by adjusting the preprocessor definitions in the client.h file:

- `LOG_ON_CMD`: Set to true to log messages to the console.
- `LOG_ON_COPPELIA`: Set to true to log messages to CoppeliaSim's status bar.

Adjust these definitions according to your logging preferences.

## Contributing

Contributions to the CoppeliaSim C++ Client are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

