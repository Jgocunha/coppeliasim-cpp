# coppeliasim-cpp

coppeliasim-cpp is a repository that contains C++ code and examples for interfacing with CoppeliaSim. 

## Prerequisites

Before running the project, make sure you have the following prerequisites:

- CoppeliaSim: Install CoppeliaSim on your machine. 
  - You can download it from the [Coppelia Robotics website](https://www.coppeliarobotics.com/downloads).
  - Set the `COPPELIASIM_ROOT_DIR` environment variable to the path of your CoppeliaSim installation directory.
- CMake: Make sure CMake is installed on your system to build the project.

## Project Overview

This repository contains multiple projects that showcase different functionalities using the legacy remote API. All projects are located in separate directories within the `coppeliasim-cpp` folder. Each project focuses on a specific use case and demonstrates how to interact with CoppeliaSim using the legacy remote API.

### Legacy Remote API Usage

To use the legacy remote API functionality in your C++ application, follow these steps:

1. Include the necessary C-language files in your project:

    - extApi.h
    - extApi.c
    - extApiPlatform.h (contains platform-specific code)
    - extApiPlatform.c (contains platform-specific code)

    These files are located in CoppeliaSim's installation directory, under `programming/legacyRemoteApi/`.

1. Also include the simLib foldet under `programming/include/`.

2. Define the following preprocessor definitions in your project configuration:

    - `NON_MATLAB_PARSING`
    - `MAX_EXT_API_CONNECTIONS=255` (optionally, you can adjust the value)
    - `DO_NOT_USE_SHARED_MEMORY` (optional, if not using shared memory)

    These definitions can be set in your CMakeLists.txt file or in your IDE's project settings.

3. Enable the legacy remote API on the server side in CoppeliaSim. To do this, add the following command to be executed once, at simulation start, in a child script of your CoppeliaSim scene:

    ```lua
    simRemoteApi.start(19999)
    ```

    Replace `19999` with the desired port number or use a different port if needed.

4. Start the simulation in CoppeliaSim.

5. Build and run your C++ project. It should establish a connection with CoppeliaSim using the legacy remote API.

## Further Resources

- CoppeliaSim Documentation: Check out the official [CoppeliaSim documentation](https://www.coppeliarobotics.com/helpFiles/index.html) for more information on using the legacy remote API and working with the simulation environment.
- Examples: Explore the projects included in this repository to see how to use the legacy remote API for different use cases.

Feel free to modify and extend the projects according to your needs. If you encounter any issues or have questions, please open an issue in this repository.