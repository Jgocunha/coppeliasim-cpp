# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- GitHub issue templates (bug report, feature request)
- GitHub pull request template
- Issue and feature backlog in `.claude/`

## [1.0.0] - 2024

### Added
- `CoppeliaSimClient` C++ class wrapping the CoppeliaSim legacy remote API
- Connection management: `initialize()`, `isConnected()`, `getClientID()`
- Simulation control: `startSimulation()`, `stopSimulation()`
- Object queries: `getObjectHandle()`, `getObjectPose()`, `getObjectPosition()`, `getObjectOrientation()`
- Signal API: get/set integer, float, and string signals
- Configurable logging via `LogMode` enum
- CMake install targets with Debug/Release separation
- Cross-platform support: Windows (MSVC + Winsock2), Linux, macOS
