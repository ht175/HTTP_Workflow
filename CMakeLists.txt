# Set the minimum required version of cmake for this project.
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

# Set the project name and optionally the version.
project(http-proxy)

# Provide an option to either build or not build the test programs.
# This is useful for users who may want to build the project without the tests.
option(BUILD_TESTS "Build test programs" ON)

# Set the C++ standard for the project to C++20.
set(CMAKE_CXX_STANDARD 20)
# Ensure that the specified C++ standard is required.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Add compiler flags to generate coverage data.
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
# Ensure that the correct file extension is used when replacing object files.
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Create a list of source files for the application.
set(APP_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/clientConnection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/request.cpp
)

# Create a list of source files for the tests.
set(TEST_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test_request.cpp
)

add_executable(http-proxy 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${APP_SRC} 
  )

# Include the 'include' directory for the 'http-proxy' target.
# This directory will be searched for header files during compilation.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)



# ---------------------------------------- Google Test Integration ---------------------------------------- #
# If building tests is enabled, set up Google Test and test targets.
if(BUILD_TESTS)
  # Enable testing functionalities provided by CMake.
  enable_testing()

  # Include the GoogleTest module to use its functionalities.
  include(GoogleTest)

  # Find the Google Test package for use with CMake.
  find_package(GTest REQUIRED)

  # Add an executable for the unit tests.
  add_executable(unit_tests 
    ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp
    ${APP_SRC} 
    ${TEST_SRC}
  )

  # Link Google Test to the test executable.
  target_link_libraries(unit_tests GTest::GTest)

  # Include the 'include' directory for the test target.
  target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

  # Discover and register all the tests found in the 'unit_tests' executable.
  gtest_discover_tests(unit_tests)
endif(BUILD_TESTS)

# ---------------------------------------- Code Coverage Report ---------------------------------------- #
# If building tests is enabled, set up a custom target for code coverage reports.
if(BUILD_TESTS)
  # Add a custom target named 'gcov' to run tests and generate a coverage report.
  add_custom_target(gcov
    COMMAND ctest
    COMMAND lcov --directory . --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1
    COMMAND genhtml code_coverage.info --branch-coverage --output-directory ./code_coverage_report/
    # This target depends on the 'unit_tests' target.
    DEPENDS unit_tests
    # Specify the working directory for the coverage commands.
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
  )
endif(BUILD_TESTS)