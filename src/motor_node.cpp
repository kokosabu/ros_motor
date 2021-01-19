#include <ros/ros.h>
#include <can_msgs/Frame.h>
#include "motor.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "motor_node");
    ros::NodeHandle nh;
    ros::Rate r(10);
    auto motor_command_pub = nh.advertise<can_msgs::Frame>("/can/send", 10, false);
    int max = 30;
    int min = 10;
    int current = 10;
    int increment = 1;
    bool rev = false;
    // auto ccmode = CurrentControl(0xDF);
    while(!ros::isShuttingDown()) {
        // ccmode.setCurrent(current);
        // auto frame = ccmode.getMessage();
        can_msgs::Frame ros_frame;
        ros_frame.dlc = 8;
        // ros_frame.id = frame->can_id;
        boost::array<uint8_t, 8> data;
        auto c_frame = ros_frame.data.c_array();
        // c_frame = frame->data;
        motor_command_pub.publish(ros_frame);
        if(current < max && !rev) {
            current += increment;
        } else if(current == max){
            rev = true;
            current -= increment;
        } else if(current > min){
            current -= increment;
        } else {
            rev = false;
            current += increment;
        }
        r.sleep();
    }
}
