cmake_minimum_required(VERSION 2.8)

project(TestJoin)

FIND_PACKAGE( Boost 1.67 COMPONENTS unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_BUILD_TYPE Debug)

set(SRC_PATH src)

set (CMAKE_CXX_STANDARD 17)

set(${PROJECT_NAME}_SRC
   ${SRC_PATH}/testJoin.cpp
)

#########################################################
# Executable
add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC} )

TARGET_LINK_LIBRARIES( ${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} )
