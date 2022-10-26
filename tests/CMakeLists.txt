
# =======
#
# Import Google Test & Google Mock
#
# =======

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 14)

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
  ${TEST_SRC_DIR}/TemplateUtil.cpp
  ${TEST_SRC_DIR}/Span.cpp
  ${TEST_SRC_DIR}/Iterator.cpp
  ${TEST_SRC_DIR}/Helpers.cpp
  ${TEST_SRC_DIR}/TypeTrait.cpp
  ${TEST_SRC_DIR}/Callback/CallbackCommon.cpp
  ${TEST_SRC_DIR}/Callback/NoReturnNoArgs.cpp
  ${TEST_SRC_DIR}/Callback/NoReturnWithArgs.cpp
  ${TEST_SRC_DIR}/Callback/WithReturnNoArgs.cpp
  ${TEST_SRC_DIR}/Callback/WithReturnWithArgs.cpp
  ${TEST_SRC_DIR}/Buffer/Operations.cpp
  ${TEST_SRC_DIR}/Buffer/Retrieval.cpp
  ${TEST_SRC_DIR}/Buffer/Iterators.cpp
  ${TEST_SRC_DIR}/Buffer/AssignmentConstructor.cpp
  ${TEST_SRC_DIR}/Buffer/Comparison.cpp
  ${TEST_SRC_DIR}/Bits/Helpers/Helpers.cpp
  ${TEST_SRC_DIR}/Bits/Helpers/BitCombinerHelpers.cpp
  ${TEST_SRC_DIR}/Bits/Helpers/BitMaskCreator.cpp
)
set(TEST_HEADER_FILES
  ${TEST_SRC_DIR}/CallbackHelper.h
)

add_executable(tests ${TEST_SRC_FILES} ${TEST_HEADER_FILES})
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests gtest_main gmock Embedded)

# MSVC doesn't support generation coverage in the same way so make it a 
# GCC/CLANG only option
if (NOT MSVC)
  target_link_options(tests PUBLIC "--coverage")
  target_compile_options(tests PRIVATE "-O0")
  target_compile_options(tests PRIVATE "--coverage")
endif()

get_target_property(TESTS_BIN_DIR tests BINARY_DIR)
get_target_property(EMBEDDED_BIN_DIR ${PROJECT_NAME} BINARY_DIR)
get_target_property(EMBEDDED_SRC_DIR ${PROJECT_NAME} SOURCE_DIR)
set(EMBEDDED_CMAKE_DIR "${EMBEDDED_BIN_DIR}/CMakeFiles/${PROJECT_NAME}.dir/src")
set(TESTS_CMAKE_DIR "${TESTS_BIN_DIR}/CMakeFiles/tests.dir")

# Add auto discover of the unit tests
include(GoogleTest)
gtest_discover_tests(tests)

add_custom_target(gcov
  DEPENDS tests
  COMMAND ctest -j 8
  WORKING_DIR ${TESTS_BIN_DIR}
)

add_custom_target(coverage
  DEPENDS gcov
  # Include the objects for the tests executable as well also have coverage for the header only libraries.
  COMMAND gcov -u -c -a $<TARGET_OBJECTS:${PROJECT_NAME}> $<TARGET_OBJECTS:tests>
  # COMMAND echo "start --include $<JOIN:$<TARGET_PROPERTY:${PROJECT_NAME},INCLUDE_DIRECTORIES>, --include > end"
  COMMAND lcov --rc lcov_branch_coverage=1 --directory "${EMBEDDED_CMAKE_DIR}" --directory "${TESTS_CMAKE_DIR}" -o coverage.info --capture  --include "\"${EMBEDDED_SRC_DIR}/include/*\""  --include "\"${EMBEDDED_SRC_DIR}/src/*\"" 
  COMMAND ${CMAKE_COMMAND} -E make_directory coverage
  COMMAND ${CMAKE_COMMAND} -E remove -f ${EMBEDDED_BIN_DIR}/*.gcov
  COMMAND ${CMAKE_COMMAND} -E remove -f ${TESTS_BIN_DIR}/*.gcov
  COMMAND genhtml --output-directory coverage/ coverage.info --rc lcov_branch_coverage=1
  COMMAND_EXPAND_LISTS
)
