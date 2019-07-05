#include "pickPlace_execute.h"
#include <iostream>
#include <ros/ros.h>
#include "geometry_msgs/Pose.h"
#include <pick_place_bridge/set_pick.h>
#include <pick_place_bridge/set_place.h>
#include <pick_place_bridge/ros_pick_place.h>
#include <pick_place_bridge/ros_stop.h>
#include <pick_place_bridge/ros_freeback.h>

using namespace hirop_pickPlace;

class PickPlaceService{
    
public:
    PickPlaceService(ros::NodeHandle n);

    ~PickPlaceService();
    
    int start();

    bool set_pick_pose_callback(pick_place_bridge::set_pick::Request &req, pick_place_bridge::set_pick::Response &res);

    bool set_pick_place_callback(pick_place_bridge::set_place::Request &req, pick_place_bridge::set_place::Response &res);

    bool pick_place_callback(pick_place_bridge::ros_pick_place::Request &req, pick_place_bridge::ros_pick_place::Response &res);

    // bool gen_pick_pose();

    // bool gen_place_pose();

    // bool pick();

    // bool place();

    bool stop_callback(pick_place_bridge::ros_stop::Request &req, pick_place_bridge::ros_stop::Response &res);

    bool freeback_callback(pick_place_bridge::ros_freeback::Request &req, pick_place_bridge::ros_freeback::Response &res);


private:
    ros::NodeHandle n_pick;

    hirop_pickPlace::PickPlace *m_pickplace;

    ros::ServiceServer set_pick;
    ros::ServiceServer set_place;
    ros::ServiceServer pick_server;
    ros::ServiceServer ros_stop;
    ros::ServiceServer ros_free;

    geometry_msgs::Pose _pickPos;
    geometry_msgs::Pose _placePos;

};
