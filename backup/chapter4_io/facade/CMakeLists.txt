# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(Facade)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
# Schedule a new version file generation after every build
add_custom_command(
    TARGET app
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
    -DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
    -DPROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}
    -P ${PROJECT_SOURCE_DIR}/build.version.cmake
    )

list(APPEND HEADERS 
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/build/include/generated"
    )
    
list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/src/es_led.c"
    "${PROJECT_SOURCE_DIR}/src/es_button.c"
    "${PROJECT_SOURCE_DIR}/src/main.c"
    
)
include_directories(${HEADERS})
target_sources(app PRIVATE ${SOURCES})

include("${PROJECT_SOURCE_DIR}/build.version.cmake")