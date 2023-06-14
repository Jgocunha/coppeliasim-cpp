# Testbed API

This project demonstrates the usage of the CoppeliaSim API in C++. It provides a basic example of connecting to CoppeliaSim, retrieving object handles, retrieving the mouse position, sending a status message, and closing the connection.

## api-testbed.cpp

The `api-testbed.cpp` file is the main source file of the project. It contains the entry point of the application and demonstrates various API calls to interact with CoppeliaSim. Here's a breakdown of its functionality:

1. It includes the necessary header files for the CoppeliaSim API and other required libraries.

2. It establishes a connection to CoppeliaSim using the `simxStart` function, providing the IP address and port number.

3. It checks if the connection was successful. If not, it displays an error message and exits.

4. It retrieves the object handles in the scene using the `simxGetObjects` function, specifying the object type as `sim_handle_all`.

5. It prints the number of objects in the scene.

6. It enters a loop to continuously retrieve the mouse position using the `simxGetIntegerParameter` function with `sim_intparam_mouse_x`. It prints the mouse position on each iteration.

7. It sends a status message to CoppeliaSim using the `simxAddStatusbarMessage` function.

8. It ensures that the last command has arrived using the `simxGetPingTime` function.

9. Finally, it closes the connection with CoppeliaSim using the `simxFinish` function.

## CMakeLists.txt

The `CMakeLists.txt` file is used by CMake to configure and build the project. It provides instructions to locate the necessary dependencies, define compilation options, and generate the build system. Here's a breakdown of its contents:

1. It specifies the minimum required version of CMake.

2. It sets the project name to `api-testbed`.

3. It includes the necessary headers and source files for the project.

4. It defines the target executable named `api-testbed` and lists the source files required to build it.

5. It sets the preprocessor definitions using the `target_compile_definitions` function. In this case, it defines `NON_MATLAB_PARSING`, `MAX_EXT_API_CONNECTIONS=255`, and `DO_NOT_USE_SHARED_MEMORY`.

6. It links the target against the CoppeliaSim API library using the `target_link_libraries` function.

7. Optionally, it sets the C++ standard to version 20 if the CMake version is greater than 3.12.