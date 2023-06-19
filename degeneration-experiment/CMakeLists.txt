cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("degeneration-experiment")

# Set the path to the CoppeliaSim API include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/coppeliasim)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    degeneration-experiment.cpp
    libs/coppeliasim/extApi.c
    libs/coppeliasim/extApiPlatform.c
    src/logger.cpp
    src/experiment.cpp
    src/client.cpp
)

# Add executable
add_executable(degeneration-experiment ${SOURCES})

# Define preprocessor definitions
target_compile_definitions(degeneration-experiment PRIVATE NON_MATLAB_PARSING MAX_EXT_API_CONNECTIONS=255 DO_NOT_USE_SHARED_MEMORY)

# Link against the CoppeliaSim API library
target_link_libraries(degeneration-experiment
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/coppeliasim/
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET degeneration-experiment PROPERTY CXX_STANDARD 20)
endif()
