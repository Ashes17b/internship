cmake_minimum_required(VERSION 2.8)

project(RuleOfFiveExample)

set(CMAKE_BUILD_TYPE Debug)

set(SRC_PATH src)

set(${PROJECT_NAME}_SRC
   ${SRC_PATH}/ruleOfFiveExample.cpp
)

#########################################################
# Executable
add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC} )
