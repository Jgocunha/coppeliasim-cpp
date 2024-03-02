cmake_minimum_required (VERSION 3.15)

project(coppeliasim-cpp-client
    DESCRIPTION "A C++ library to interface with Coppeliasim."
    #LANGUAGES CXX
)

# Define library version
set(COPPELIASIM_CLIENT_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(COPPELIASIM_CLIENT_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(COPPELIASIM_CLIENT_VERSION ${COPPELIASIM_CLIENT_VERSION_MAJOR}.${COPPELIASIM_CLIENT_VERSION_MINOR} CACHE STRING "version" FORCE)

set(COPPELIASIM_CLIENT_LIB_PREFIX "release")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(COPPELIASIM_CLIENT_LIB_PREFIX "debug")
endif()

set(COPPELIASIM_CLIENT_INC_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(COPPELIASIM_CLIENT_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(COPPELIASIM_CLIENT_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/${COPPELIASIM_CLIENT_LIB_PREFIX}")
set(COPPELIASIM_CLIENT_ARCHIVE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/${COPPELIASIM_CLIENT_LIB_PREFIX}")
set(COPPELIASIM_CLIENT_FRAMEWORK_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(COPPELIASIM_CLIENT_CMAKE_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}")
set(COPPELIASIM_CLIENT_ADDITIONAL_FILES_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}")

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set sources
set(sources
    src/client.cpp

    lib/extApi.c
    lib/extApiPlatform.c

    lib/simLib/luaFunctionData.cpp
    lib/simLib/luaFunctionDataItem.cpp
    lib/simLib/scriptFunctionData.cpp
    lib/simLib/scriptFunctionDataItem.cpp
    lib/simLib/shared_memory.c
    #lib/simLib/simLib-old.cpp
    #lib/simLib/simLib-old2.cpp
    lib/simLib/simLib.cpp
    lib/simLib/socketInConnection.cpp
    lib/simLib/socketOutConnection.cpp
)

# Set headers
set(client_headers
	include/client.h
)
set(api_headers
    lib/extApi.h
    lib/extApiPlatform.h
	lib/extApiInternal.h
)
set(simLib_headers
    lib/simLib/luaFunctionData.h
	lib/simLib/luaFunctionDataItem.h
	lib/simLib/scriptFunctionData.h
	lib/simLib/scriptFunctionDataItem.h
	lib/simLib/shared_memory.h
    lib/simLib/simConst.h
    lib/simLib/simExp.h
	#lib/simLib/simLib-old.h
	#lib/simLib/simLib-old2.h
	lib/simLib/simLib.h
    lib/simLib/simTypes.h
	lib/simLib/socketInConnection.h
	lib/simLib/socketOutConnection.h
    lib/simLib/_dirent.h
)

add_library(coppeliasim-cpp-client
	${sources}
	${client_headers}
	${api_headers}
    ${simLib_headers}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> 
    $<INSTALL_INTERFACE:${COPPELIASIM_CLIENT_INC_INSTALL_DIR}> 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
    COPPELIASIM_CLIENT=1
    COPPELIASIM_CLIENT_VERSION_MAJOR=${COPPELIASIM_CLIENT_VERSION_MAJOR}
    COPPELIASIM_CLIENT_VERSION_MINOR=${COPPELIASIM_CLIENT_VERSION_MINOR}
    NON_MATLAB_PARSING 
    MAX_EXT_API_CONNECTIONS=255 
    DO_NOT_USE_SHARED_MEMORY
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${CMAKE_PROJECT_NAME}-${COPPELIASIM_CLIENT_VERSION}"
    POSITION_INDEPENDENT_CODE ON
)

install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${CMAKE_PROJECT_NAME}Targets
    RUNTIME       DESTINATION ${COPPELIASIM_CLIENT_RUNTIME_INSTALL_DIR}
    LIBRARY       DESTINATION ${COPPELIASIM_CLIENT_LIBRARY_INSTALL_DIR}
    ARCHIVE       DESTINATION ${COPPELIASIM_CLIENT_ARCHIVE_INSTALL_DIR}
    FRAMEWORK     DESTINATION ${COPPELIASIM_CLIENT_FRAMEWORK_INSTALL_DIR}
)

include(CMakePackageConfigHelpers)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/cmake/${CMAKE_PROJECT_NAME}-config-version.cmake")
write_basic_package_version_file(${version_file}
    VERSION ${COPPELIASIM_CLIENT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Install headers
install(FILES ${client_headers} DESTINATION ${COPPELIASIM_CLIENT_INC_INSTALL_DIR})
install(FILES ${api_headers} DESTINATION ${COPPELIASIM_CLIENT_INC_INSTALL_DIR})
install(FILES ${simLib_headers} DESTINATION ${COPPELIASIM_CLIENT_INC_INSTALL_DIR}/simLib)



install(EXPORT ${CMAKE_PROJECT_NAME}Targets DESTINATION ${COPPELIASIM_CLIENT_CMAKE_CONFIG_INSTALL_DIR}
    FILE ${CMAKE_PROJECT_NAME}-config.cmake
)

# Add executable project
set(EXE_PROJECT ${CMAKE_PROJECT_NAME}-exe)
add_executable(${EXE_PROJECT} "coppeliasim-cpp-client.cpp")
#target_include_directories(${EXE_PROJECT} PRIVATE include)
target_link_libraries(${EXE_PROJECT} PRIVATE ${CMAKE_PROJECT_NAME})