cmake_minimum_required(VERSION 2.8.3)
project(FIFTH)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)
find_package(OpenCV REQUIRED )
include_directories(
include
  ${catkin_INCLUDE_DIRS}
)
add_executable(thr src/thr.cpp)
target_link_libraries(thr ${catkin_LIBRARIES}${OpenCV_LIBS})
add_dependencies(thr FOURTH_generate_messages_cpp)


