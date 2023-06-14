cmake_minimum_required(VERSION 3.8)

project(api-testbed)

# Set the path to the CoppeliaSim API include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/coppeliasim)

# Add source files
add_executable(api-testbed "api-testbed.cpp" 
 "libs/coppeliasim/extApi.c" "libs/coppeliasim/extApiPlatform.c")

# Define preprocessor definitions
target_compile_definitions(api-testbed PRIVATE NON_MATLAB_PARSING MAX_EXT_API_CONNECTIONS=255 DO_NOT_USE_SHARED_MEMORY)


# Link against the CoppeliaSim API library
target_link_libraries(api-testbed ${CMAKE_CURRENT_SOURCE_DIR}/libs/coppeliasim/)

# Set the C++ standard (optional)
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET api-testbed PROPERTY CXX_STANDARD 20)
endif()