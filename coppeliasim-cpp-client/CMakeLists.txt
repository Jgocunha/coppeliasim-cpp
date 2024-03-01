cmake_minimum_required(VERSION 3.15)
project(coppeliasim-cpp-client DESCRIPTION "A C++ library that interfaces with CoppeliaSim using their C++ API." LANGUAGES CXX)

# Library version
set(COPPELIASIM_CLIENT_VERSION_MAJOR 1)
set(COPPELIASIM_CLIENT_VERSION_MINOR 0)
set(COPPELIASIM_CLIENT_VERSION ${COPPELIASIM_CLIENT_VERSION_MAJOR}.${COPPELIASIM_CLIENT_VERSION_MINOR})

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source and header files
set(libs lib/extApi.c lib/extApiPlatform.c)
set(sources src/client.cpp)
#set(headers include/client.h)

# Library target
add_library(${PROJECT_NAME} lib/extApi.c lib/extApiPlatform.c src/client.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# For the library target
target_compile_definitions(${PROJECT_NAME} PRIVATE NON_MATLAB_PARSING MAX_EXT_API_CONNECTIONS=255 DO_NOT_USE_SHARED_MEMORY)


# Executable target
set(EXE_PROJECT ${PROJECT_NAME}-exe)
add_executable(${EXE_PROJECT} "client-example.cpp")
target_link_libraries(${EXE_PROJECT} PRIVATE ${PROJECT_NAME})
#target_include_directories(${EXE_PROJECT} PRIVATE include lib)
