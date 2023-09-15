#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
    // Initialize the ROS node
    ros::init(argc, argv, "turtle_expanding_spiral");
    ros::NodeHandle nh;

    // Create a publisher to send velocity commands
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    // Set the loop rate (adjust this according to your needs)
    ros::Rate loop_rate(10);

    double linear_speed = 1.0;   // Initial linear speed
    double angular_speed = 1.0;  // Initial angular speed
    double linear_increment = 0.1;
    double angular_increment = 0.1;

    while (ros::ok())
    {
        // Create a Twist message to send velocity commands
        geometry_msgs::Twist msg;

        // Set the linear and angular velocities
        msg.linear.x = linear_speed;
        msg.angular.z = angular_speed;

        // Publish the velocity command
        cmd_vel_pub.publish(msg);

        // Increase linear and angular speeds for an expanding spiral motion
        linear_speed += linear_increment;
        angular_speed += angular_increment;

        // Update the loop
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
