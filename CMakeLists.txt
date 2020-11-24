cmake_minimum_required(VERSION 2.8.3)
project(gaussian_process_regression)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_BUILD_TYPE Release)
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED COMPONENTS   
message_generation
  roscpp
  rospy
  std_msgs)
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS  roscpp rospy std_msgs message_runtime
#  LIBRARIES gaussian_process_regression
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)
include_directories(include 
${catkin_INCLUDE_DIRS} )
include_directories("/home/mxr/catkin_gpr/src/gaussian-process-regression/include/")
#add_executable(test_gpr src/test_gpr.cpp)
#target_link_libraries(test_gpr ${catkin_LIBRARIES} gtest pthread)
add_executable(my_test src/my_test.cpp)
target_link_libraries(my_test ${catkin_LIBRARIES})
add_executable(prac src/prac.cpp)
target_link_libraries(prac ${catkin_LIBRARIES} gtest pthread)
###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations


#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
if(CATKIN_ENABLE_TESTING)
  catkin_add_gtest(${PROJECT_NAME}-test
    test/test_gpr.cpp
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    )
endif()



