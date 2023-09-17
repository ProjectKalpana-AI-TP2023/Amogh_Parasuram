#include <rclcpp/rclcpp.hpp>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>

class SpiralTurtleNode : public rclcpp::Node
{
public:
    SpiralTurtleNode()
        : Node("spiral_turtle")
    {
        cmd_pub_ = create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        pose_sub_ = create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, std::bind(&SpiralTurtleNode::poseCallback, this, std::placeholders::_1));

        timer_ = create_wall_timer(std::chrono::milliseconds(100), std::bind(&SpiralTurtleNode::update, this));

        linear_vel_ = 1.0;  // Initial linear velocity
        angular_vel_ = 0.2; // Initial angular velocity
        radius_ = 1.0;      // Initial radius
    }

private:
    void poseCallback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        current_pose_ = *msg;
    }

    void update()
    {
        geometry_msgs::msg::Twist cmd_vel;
        cmd_vel.linear.x = linear_vel_;
        cmd_vel.angular.z = angular_vel_;

        cmd_pub_->publish(cmd_vel);

        // Increase the linear velocity and expand the spiral
        linear_vel_ += 0.1;
        radius_ += 0.1;
        angular_vel_ = linear_vel_ / radius_;
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_sub_;
    rclcpp::TimerBase::SharedPtr timer_;
    turtlesim::msg::Pose current_pose_;
    double linear_vel_;
    double angular_vel_;
    double radius_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SpiralTurtleNode>());
    rclcpp::shutdown();
    return 0;
}

