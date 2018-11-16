cmake_minimum_required(VERSION 2.8)

project(TestLogger)

set(CMAKE_BUILD_TYPE Debug)

set(SRC_PATH src)

set (CMAKE_CXX_STANDARD 17)

set(${PROJECT_NAME}_SRC
   ${SRC_PATH}/testLogger.cpp
)

#########################################################
# Executable
add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC} )
