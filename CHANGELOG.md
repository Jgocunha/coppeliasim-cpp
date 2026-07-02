# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Cross-platform CI workflow (GitHub Actions) building on Windows, Linux, and macOS (Debug/Release)
- GoogleTest unit-test suite (`tests/`) with a fake `simx*` layer for simulator-free functional tests
- Static analysis (clang-tidy + cppcheck) and ASan/UBSan sanitizer CI jobs
- `CoppeliaSimClient::connect()` factory returning `std::optional<CoppeliaSimClient>`
- Move semantics for `CoppeliaSimClient` (copy remains disabled)
- Simulation control: `pauseSimulation()`
- Connection health: `getPingTime()`
- Object setters: `setObjectPosition()`, `setObjectOrientation()`
- Object queries: `getObjectVelocity()`, `getObjectChild()`, `getObjectChildren()`
- Joint control: `getJointPosition()`, `setJointTargetPosition()`, `setJointTargetVelocity()`
- Scene management: `loadScene()`, `closeScene()`
- GitHub issue templates (bug report, feature request)
- GitHub pull request template
- Issue and feature backlog in `.claude/`
- Top-level MIT `LICENSE` (the vendored CoppeliaSim sources under `lib/` keep their own license)
- `.clang-format` codifying the existing style, enforced by a CI format check

### Changed
- Query methods now return `std::optional<T>` and command methods return `bool`, so API-call
  failures are reported instead of returning fabricated values
- Default `LogMode` is now `NO_LOGS` (was `LOG_COPPELIA_CMD`)
- `Position`/`Orientation`/`Pose` are now aggregates
- Renamed `log_msg` to `logMsg`; `setFloatSignal` now takes `float` by value
- Made the library compile on Linux/macOS (guarded Windows-only includes)
- Rewrote the root README to describe the vendored single-library layout
- Moved the demo executable to `examples/pose_tracker.cpp` and removed the
  `coppeliasim-cpp-client.h` shim header
- Only the remote-API client sources are compiled now; the plugin-side `simLib/`
  tree is kept as vendored reference (its `simConst.h` still ships, as `extApi.h` needs it)
- CMake version is declared once via `project(VERSION 0.0.1)` and matches the CHANGELOG

### Fixed
- Out-of-bounds read in `isConnected()`/`getStringSignal()` when called with an invalid
  connection or on a failed API call (caught by UBSan/ASan)
- `isConnected()` now respects `LogMode` instead of printing to stdout unconditionally

## [0.0.1] - 2024

### Added
- `CoppeliaSimClient` C++ class wrapping the CoppeliaSim legacy remote API
- Connection management: `initialize()`, `isConnected()`, `getClientID()`
- Simulation control: `startSimulation()`, `stopSimulation()`
- Object queries: `getObjectHandle()`, `getObjectPose()`, `getObjectPosition()`, `getObjectOrientation()`
- Signal API: get/set integer, float, and string signals
- Configurable logging via `LogMode` enum
- CMake install targets with Debug/Release separation
- Cross-platform support: Windows (MSVC + Winsock2), Linux, macOS
