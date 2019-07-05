#include <ros/ros.h>
#include "ros_pick_place.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pick_place_bridge");
    ros::NodeHandle n;

    PickPlaceService s(n);
    s.start();
    ros::spin();
    return 0;
}