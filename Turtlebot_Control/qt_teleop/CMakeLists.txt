cmake_minimum_required(VERSION 3.0.2)
project(qt_teleop)

find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(qt_teleop_node
    src/main.cpp
    src/teleop_widget.cpp
)

target_link_libraries(qt_teleop_node
    ${catkin_LIBRARIES}
    Qt5::Widgets
)

