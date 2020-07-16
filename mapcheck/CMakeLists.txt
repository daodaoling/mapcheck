cmake_minimum_required(VERSION 3.0.2)
project(mapcheck)

find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  rosbag
  cv_bridge
  #OpenCV
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES example_cpp
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  #${OpenCV_INCLUDE_DIRS}
)

add_executable(rosbagcheck src/rosbagcheck.cpp)
add_executable(mapgencheck src/mapgencheck.cpp)

add_dependencies(rosbagcheck example_cpp_generate_messages_cpp)
add_dependencies(mapgencheck example_cpp_generate_messages_cpp)

target_link_libraries(mapgencheck ${catkin_LIBRARIES} mysqlclient)
target_link_libraries(mapgencheck ${catkin_LIBRARIES} curl)
target_link_libraries(rosbagcheck ${catkin_LIBRARIES} curl)
target_link_libraries(rosbagcheck libjsoncpp.a)

