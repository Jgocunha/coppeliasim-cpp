cmake_minimum_required(VERSION 3.8)
project(coppeliasim-cpp-client DESCRIPTION "A C++ library that interfaces with CoppeliaSim using their C++ API." LANGUAGES CXX)




# Set the path to the CoppeliaSim API include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/coppeliasim)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set sources
set(sources
	"libs/coppeliasim/extApi.c"
	"libs/coppeliasim/extApiPlatform.c"
	#"src/client.cpp"
)

set(headers
	#"include/client.h"
)

add_library(${PROJECT_NAME}
	${sources}
	${headers}
)

# Define preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE NON_MATLAB_PARSING MAX_EXT_API_CONNECTIONS=255 DO_NOT_USE_SHARED_MEMORY)


# Link against the CoppeliaSim API library
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/libs/coppeliasim/)


add_executable(${PROJECT_NAME}_example "client-example.cpp")
#target_link_libraries(${PROJECT_NAME}_example PRIVATE ${PROJECT_NAME})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()