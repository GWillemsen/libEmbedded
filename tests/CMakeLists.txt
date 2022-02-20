
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
    ${TEST_SRC_DIR}/tests.cpp
)
set(TEST_HEADER_FILES
)

add_executable(tests ${TEST_SRC_FILES} ${TEST_HEADER_FILES})
target_link_libraries(tests gtest_main gmock)

# Add auto discover of the unit tests
include(GoogleTest)
gtest_discover_tests(tests)
