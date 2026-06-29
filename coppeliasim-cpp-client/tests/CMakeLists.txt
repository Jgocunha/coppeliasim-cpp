# GoogleTest suite for coppeliasim-cpp-client.
# Fetched at configure time so no system install is needed (CI-friendly).
include(FetchContent)
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
# Make GTest use the same (shared) MSVC runtime as our targets.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Build GTest as static libs so the test exes have no gtest/gmock DLLs to locate
# at run time (avoids load-time failures on Windows). Directory-scoped so it does
# not affect the parent library target.
set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# --- Tier 1 (pure logic) + Tier 3 (real networking stack) -----------------
# Links the real library, so the genuine simx* implementation is used.
add_executable(coppeliasim_cpp_tests
    test_structs.cpp
    test_client_realstack.cpp)
target_link_libraries(coppeliasim_cpp_tests PRIVATE
    coppeliasim-cpp-client
    GTest::gtest_main)
gtest_discover_tests(coppeliasim_cpp_tests)

# --- Tier 2 (functional, fake simx* layer) --------------------------------
# Compiles client.cpp against fake_simx.cpp INSTEAD of extApi.c/extApiPlatform.c,
# so tests control the API responses without a live simulator.
add_executable(coppeliasim_cpp_functional_tests
    test_client_functional.cpp
    fake_simx.cpp
    ${PROJECT_SOURCE_DIR}/src/client.cpp)
target_include_directories(coppeliasim_cpp_functional_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib)
target_compile_definitions(coppeliasim_cpp_functional_tests PRIVATE
    NON_MATLAB_PARSING
    MAX_EXT_API_CONNECTIONS=255
    DO_NOT_USE_SHARED_MEMORY)
target_compile_features(coppeliasim_cpp_functional_tests PRIVATE cxx_std_20)
target_link_libraries(coppeliasim_cpp_functional_tests PRIVATE GTest::gtest_main)
gtest_discover_tests(coppeliasim_cpp_functional_tests)
