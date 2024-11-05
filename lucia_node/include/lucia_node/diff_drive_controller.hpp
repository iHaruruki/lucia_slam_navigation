#ifndef LUCIA_NODE__DIFF_DRIVE_CONTROLLER_HPP_
#define LUCIA_NODE__DIFF_DRIVE_CONTROLLER_HPP_

#include <memory>
#include <rclcpp/rclcpp.hpp>

namespace robotis
{
    namespace lucia
    {
        class DiffDriveController
        {
            public:
                explicit DiffDriveController(const float wheel_seperation, const float wheel_radius);
                virtual ~DiffDriveController(){}

            private:
                std::shared_ptr<rclcpp::Node> nh_;
                std::unique_ptr<Odometry> odometry_;
        };
    }
}
#endif