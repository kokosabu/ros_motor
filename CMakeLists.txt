cmake_minimum_required(VERSION 3.0.2)
project(ros_motor)
add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  can_msgs
  roscpp
  socketcan_interface
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_motor
CATKIN_DEPENDS can_msgs roscpp socketcan_interface
#  DEPENDS system_lib
)
add_subdirectory(lib/motor/)
include_directories(

  ${catkin_INCLUDE_DIRS}
)
add_executable(motor_node src/motor_node.cpp)
target_link_libraries(motor_node ${catkin_LIBRARIES})
