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

### 1. Connect

Use the `connect()` factory. It establishes the connection and returns a
`std::optional<CoppeliaSimClient>` — `std::nullopt` if the connection failed, so a
returned client is always connected:

```cpp
#include "coppeliasim-cpp-client.h"

int main()
{
    auto client = coppeliasim_cpp::CoppeliaSimClient::connect(
        "127.0.0.1", 19999, coppeliasim_cpp::LogMode::LOG_CMD);
    if (!client)
    {
        std::cerr << "Failed to connect to CoppeliaSim.\n";
        return 1;
    }

    // use *client / client-> ...
}
```

(If you need to construct first and connect later, the constructor plus
`[[nodiscard]] bool initialize()` are still available, but `connect()` is preferred.)

### 2. Call methods

Commands return `bool` (success); queries return `std::optional<T>` (`std::nullopt`
on failure) — so failures are reported rather than returning fabricated values:

```cpp
if (!client->startSimulation()) { /* handle failure */ }

if (const auto handle = client->getObjectHandle("Cuboid"))
{
    if (const auto pose = client->getObjectPose(*handle))
    {
        // use pose->position, pose->orientation
    }
}

const bool ok = client->setIntegerSignal("speed", 42);   // commands return bool
const std::optional<int> v = client->getIntegerSignal("speed");
```

Available methods include simulation control (`startSimulation`, `stopSimulation`,
`pauseSimulation`), signals (`set/getIntegerSignal`, `set/getFloatSignal`,
`set/getStringSignal`), object queries and setters (`getObjectHandle`,
`getObjectPose/Position/Orientation/Velocity`, `setObjectPosition/Orientation`,
`getObjectChild/Children`), joint control (`getJointPosition`,
`setJointTargetPosition/Velocity`), scene management (`loadScene`, `closeScene`),
connection health (`isConnected`, `getPingTime`), and logging (`logMsg`).

### 3. Clean up

Cleanup is automatic — the destructor releases the connection (`simxFinish`). The
client is movable but not copyable.

### Logging

The CoppeliaSim C++ Client provides a logging mechanism to output messages. You control where messages go by passing a `LogMode` to the constructor (or `connect`); the default is `LogMode::NO_LOGS`:

- `LogMode::NO_LOGS`: no logging (default).
- `LogMode::LOG_CMD`: log messages to the console.
- `LogMode::LOG_COPPELIA`: log messages to CoppeliaSim's status bar.
- `LogMode::LOG_COPPELIA_CMD`: log to both.

You can change it at runtime with `setLogMode(LogMode)`.

## Contributing

Contributions to the CoppeliaSim C++ Client are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

