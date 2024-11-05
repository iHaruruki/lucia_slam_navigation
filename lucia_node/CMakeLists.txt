cmake_minimum_required(VERSION 3.5)
project(lucia_node)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
fild_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(message_filters REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rcutils REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(turtlebot3_msgs REQUIRED)

include_directories(
    include
)

add_library(${PROJECT_NAME}_lib
    "src/odometry.cpp"
    "src/joint_state.cpp"
    "src/sensors/sensor_state.cpp"
)

set(DEPENDENCIES
  "geometry_msgs"
  "message_filters"
  "nav_msgs"
  "rclcpp"
  "rcutils"
  "sensor_msgs"
  "std_msgs"
  "std_srvs"
  "tf2"
  "tf2_ros"
  "turtlebot3_msgs"
)

target_link_libraries(${PROJECT_NAME}_lib)
amet_target_dependencies(${PROJECT_NAME}_lib ${DEPENDENCIES})

include(DIRECTORY param
    DESTINATION share/${PROJECT_NAME}
)

install(TARGETS ${EXECUTABLE_NAME}
    DESTINATION lib/${PROJECT_NAME}
)

ament_cmake_include_directories(include)
ament_package()