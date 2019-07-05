cmake_minimum_required(VERSION 2.8.3)
project(pick_place_bridge)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE EXTRA_FILES */*)
add_custom_target(${PROJECT_NAME}_OTHER_FILES ALL WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} SOURCES ${EXTRA_FILES})

## Compile as C++11, supported in ROS Kinetic and newer
 #add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
  geometry_msgs
  message_generation
)

## Generate services in the 'srv' folder
add_service_files(FILES
  ros_freeback.srv
  ros_stop.srv
  set_place.srv
  set_pick.srv
  ros_pick_place.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(DEPENDENCIES
  std_msgs
  geometry_msgs
)

catkin_package(
  CATKIN_DEPENDS
  message_runtime
#  INCLUDE_DIRS include
#  LIBRARIES pick_place_bridge
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
  include
  /home/shen/catkin_ws/src/hirop_pickandplace/hirop_PickPlace/
  /home/shen/catkin_ws/src/hirop_pickandplace/hirop_PickPlace/include
  ${catkin_INCLUDE_DIRS}
)
include_directories(/home/shen/yaml-cpp/include/)

LINK_DIRECTORIES(/home/shen/catkin_ws/src/hirop_pickandplace/install_libs
                 /home/shen/catkin_ws/src/yaml-cpp/build)

add_executable(pick_place_bridge
  src/main.cpp
  src/ros_pick_place.cpp
)
add_dependencies(pick_place_bridge ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(pick_place_bridge
  hirop_pickandplace
  yaml-cpp
  ${catkin_LIBRARIES}
)
