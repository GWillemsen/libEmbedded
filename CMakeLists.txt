cmake_minimum_required(VERSION 3.16.0)
project(Embedded CXX)

option(BUILD_TEST "Also build the unit tests for the library." OFF)

# =========
#
# Actual library target build
#
# =========
set(${PROJECT_NAME}_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/libEmbedded)
set(${PROJECT_NAME}_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(${PROJECT_NAME}_HEADERS 
        ${${PROJECT_NAME}_HEADERS_DIR}/Buffer.h
        ${${PROJECT_NAME}_HEADERS_DIR}/Callback.h
        ${${PROJECT_NAME}_HEADERS_DIR}/EdgeDetector.h
        ${${PROJECT_NAME}_HEADERS_DIR}/TemplateUtil.h
        ${${PROJECT_NAME}_HEADERS_DIR}/Span.h
        ${${PROJECT_NAME}_HEADERS_DIR}/bits/Helpers.h
)
        
set(${PROJECT_NAME}_SOURCES
    ${${PROJECT_NAME}_SOURCE_DIR}/EdgeDetector.cpp
    ${${PROJECT_NAME}_SOURCE_DIR}/bits/Helpers.cpp
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_11
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "debug")
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "debug")
    if (${BUILD_TEST})
        target_compile_options(${PROJECT_NAME} PRIVATE "--coverage")
        target_compile_options(${PROJECT_NAME} PRIVATE "-O0")
        target_link_options(${PROJECT_NAME} PUBLIC "--coverage")
    endif()
endif()

# =========
#
# Extra additional features/things
#
# =========

if (${BUILD_TEST})
    add_subdirectory(tests)
endif()
