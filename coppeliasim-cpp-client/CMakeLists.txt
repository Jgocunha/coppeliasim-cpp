cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("coppeliasim-cpp-client")

# Set the path to the CoppeliaSim API include directory
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/coppeliasim)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
#set(SOURCES
#    coppeliasim-cpp-client.cpp
#    lib/coppeliasim/extApi.c
#    lib/coppeliasim/extApiPlatform.c
#    src/client.cpp
#)

add_library(coppeliasim-cpp-client
	lib/coppeliasim/extApi.c
    lib/coppeliasim/extApiPlatform.c
    src/client.cpp
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET coppeliasim-cpp-client PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(coppeliasim-cpp-client PUBLIC ${PROJECT_SOURCE_DIR}/lib/coppeliasim)
target_include_directories(coppeliasim-cpp-client PUBLIC ${PROJECT_SOURCE_DIR}/include)


# Add source to this project's executable.
add_executable (launch-coppeliasim-cpp-client "coppeliasim-cpp-client.cpp")

# Define preprocessor definitions
target_compile_definitions(coppeliasim-cpp-client PRIVATE NON_MATLAB_PARSING MAX_EXT_API_CONNECTIONS=255 DO_NOT_USE_SHARED_MEMORY)

# Link against the CoppeliaSim API library
target_link_libraries(launch-coppeliasim-cpp-client PRIVATE coppeliasim-cpp-client)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET launch-coppeliasim-cpp-client PROPERTY CXX_STANDARD 20)
endif()