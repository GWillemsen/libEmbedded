
# =======
#
# Import Google Test & Google Mock
#
# =======

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# =======
#
# Actual unit test target
#
# =======
enable_testing()

set(TEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_SRC_FILES
    ${TEST_SRC_DIR}/EdgeDetector.cpp
)
set(TEST_HEADER_FILES
)

add_executable(tests ${TEST_SRC_FILES} ${TEST_HEADER_FILES})
target_link_libraries(tests gtest_main gmock Embedded)

get_target_property(TESTS_BIN_DIR tests BINARY_DIR)
get_target_property(EMBEDDED_BIN_DIR ${PROJECT_NAME} BINARY_DIR)
get_target_property(EMBEDDED_SRC_DIR ${PROJECT_NAME} SOURCE_DIR)
set(EMBEDDED_BIN_DIR "${EMBEDDED_BIN_DIR}/CMakeFiles/${PROJECT_NAME}.dir/src")

# Add auto discover of the unit tests
include(GoogleTest)
gtest_discover_tests(tests)

add_custom_target(gcov
  DEPENDS tests
  COMMAND ctest
  WORKING_DIR ${TESTS_BIN_DIR}
)

add_custom_target(coverage
  DEPENDS gcov
  # Include the objects for the tests executable as well also have coverage for the header only libraries.
  COMMAND gcov -u -c -a $<TARGET_OBJECTS:${PROJECT_NAME}> $<TARGET_OBJECTS:tests>
  # COMMAND echo "start --include $<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME},INCLUDE_DIRECTORIES>, --include > end"
  COMMAND lcov --rc lcov_branch_coverage=1 --directory "${EMBEDDED_BIN_DIR}" -o coverage.info --capture --include "\"${EMBEDDED_SRC_DIR}/*\"" 
  COMMAND ${CMAKE_COMMAND} -E make_directory coverage
  COMMAND genhtml --output-directory coverage/ coverage.info --rc lcov_branch_coverage=1
)
