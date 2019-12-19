cmake_minimum_required(VERSION 2.8.3)
project(SIXTH)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)
find_package(OpenCV REQUIRED )
include_directories(
include
  ${catkin_INCLUDE_DIRS}
)
add_executable(angle src/angle.cpp)
target_link_libraries(angle ${catkin_LIBRARIES} ${OpenCV_LIBS})



