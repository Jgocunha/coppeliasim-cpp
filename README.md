# coppeliasim-cpp

coppeliasim-cpp provides a C++ library for interfacing with [CoppeliaSim](https://www.coppeliarobotics.com/) through its legacy remote API.

The library lives in [`coppeliasim-cpp-client/`](coppeliasim-cpp-client/) — see its [README](coppeliasim-cpp-client/README.md) for the API overview and usage examples.

## Prerequisites

- **CMake** (3.15 or newer) and a C++20 compiler to build the project.
- **CoppeliaSim** to *run* against a live simulator. The library vendors the legacy
  remote API sources (under `coppeliasim-cpp-client/lib/`), so CoppeliaSim is **not**
  required to build — only to run. You can download it from the
  [Coppelia Robotics website](https://www.coppeliarobotics.com/downloads).

## Building

```sh
cd coppeliasim-cpp-client
cmake -B build
cmake --build build
ctest --test-dir build
```

CMake presets are also available (see `coppeliasim-cpp-client/CMakePresets.json`).

## Running against CoppeliaSim

1. Enable the legacy remote API on the server side. Add the following command to be
   executed once, at simulation start, in a child script of your CoppeliaSim scene:

    ```lua
    simRemoteApi.start(19999)
    ```

    Replace `19999` with a different port if needed (the client's default is 19999).
    A ready-made scene is included at `coppeliasim-cpp-client/scene.ttt`.

2. Start the simulation in CoppeliaSim.

3. Build and run your C++ program. It should establish a connection with CoppeliaSim
   using the legacy remote API.

## Using the vendored legacy remote API directly

If you want to use the raw C API in your own project instead of the C++ client, the
required files are already vendored in this repository:

- `coppeliasim-cpp-client/lib/extApi.h` / `extApi.c`
- `coppeliasim-cpp-client/lib/extApiPlatform.h` / `extApiPlatform.c` (platform-specific code)

Define the following preprocessor definitions in your project configuration
(this repository's CMakeLists.txt does this already):

- `NON_MATLAB_PARSING`
- `MAX_EXT_API_CONNECTIONS=255` (the value is adjustable)
- `DO_NOT_USE_SHARED_MEMORY` (optional, if not using shared memory)

## Further Resources

- CoppeliaSim Documentation: Check out the official [CoppeliaSim documentation](https://www.coppeliarobotics.com/helpFiles/index.html) for more information on using the legacy remote API and working with the simulation environment.

Feel free to modify and extend the project according to your needs. If you encounter any issues or have questions, please open an issue in this repository.

## License

This project is licensed under the [MIT License](LICENSE). The vendored
CoppeliaSim legacy remote API sources under `coppeliasim-cpp-client/lib/` are
third-party code distributed under their own license — see
[`coppeliasim-cpp-client/lib/license.txt`](coppeliasim-cpp-client/lib/license.txt).
