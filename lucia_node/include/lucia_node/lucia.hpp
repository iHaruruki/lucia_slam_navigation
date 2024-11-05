#ifndef LUCIA_NODE__LUCIA_HPP_
#define LUCIA_NODE__LUCIA_HPP_

#include <array>
#include <chrono>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <queue>

#include <tf2_ros/transform_broadcaster.h>

#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/battery_state.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

namespace robotis
{
    namespace lucia
    {
        extern const ControlTable extern_control_table;
        class lucia : public rclcpp::Node
        {
        public:
            typedef struct
            {
                float separation;
                float radius;   
            }wheels;

            wheels * get_wheels();
            
        private:
            void check_device_status();

            void add_wheels();

            void run();

            void publish_timer(const std::chrono::milliseconds timeout);
            void heartbeat_timer(const std::chrono::milliseconds timeout);

            void cmd_vel_callback();
            void parameter_evet_callback();

            wheels wheels_;

            std::list<sensors::Sensors *> sensors_;
            std::map<std::string, devices::Devices *> devices_;

            std::unique_ptr<Odometry> odom_;

            rclcpp::Node::SharedPtr node_handle_;

            rclcpp::TimerBase::SharedPtr publisher_timer_;
            rclcpp::TimerBase::SharedPtr heartbeat_timer_;

            rclcpp::Subscription<geometry_msgs::msg::ParameterEvent>::SharePtr parameter_event_sub_;
        };
    }
}
#endif