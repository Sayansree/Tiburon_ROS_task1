cmake_minimum_required(VERSION 2.8.3)
project(SEVENTH)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)
find_package(OpenCV REQUIRED )
include_directories(
include
  ${catkin_INCLUDE_DIRS}
)
add_executable(gate src/gate.cpp)
target_link_libraries(gate ${catkin_LIBRARIES} ${OpenCV_LIBS})



