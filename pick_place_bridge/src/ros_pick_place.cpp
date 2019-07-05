#include "ros_pick_place.h"

PickPlaceService::PickPlaceService(ros::NodeHandle n)
{
    this->n_pick = n;
    m_pickplace = new hirop_pickPlace::PickPlace();
}

PickPlaceService::~PickPlaceService()
{
    m_pickplace = NULL;
    delete m_pickplace;
}

int PickPlaceService::start()
{
    set_pick = n_pick.advertiseService("set_pick_pose", &PickPlaceService::set_pick_pose_callback, this);
    set_place = n_pick.advertiseService("set_place_pose", &PickPlaceService::set_pick_place_callback, this);
    pick_server = n_pick.advertiseService("pick_place", &PickPlaceService::pick_place_callback, this);
    ros_stop = n_pick.advertiseService("pick_stop",&PickPlaceService::stop_callback, this);
    ros_free = n_pick.advertiseService("pick_freeback",&PickPlaceService::freeback_callback, this);
    //std::cout<<"pick_place_service already started!"<<std::endl;
    ROS_INFO("pick_place_service already started!");
}

bool PickPlaceService::set_pick_pose_callback(pick_place_bridge::set_pick::Request &req, pick_place_bridge::set_pick::Response &res)
{
    this->_pickPos = req.pickPos;
    std::cout<<"set_pick_pose succeed!!!"<<std::endl;
    res.isSetFinsh = true;
    return true;
}

 bool PickPlaceService::set_pick_place_callback(pick_place_bridge::set_place::Request &req, pick_place_bridge::set_place::Response &res)
 {
     this->_placePos = req.placePos;
     std::cout<<"set_pick_place succeed!!!"<<std::endl;
     res.isSetFinsh = true;
     return true;
 }

 bool PickPlaceService::pick_place_callback(pick_place_bridge::ros_pick_place::Request &req, pick_place_bridge::ros_pick_place::Response &res)
 {
     int ret = -2;
     if(_pickPos.position.x == 0||_placePos.position.x == 0)
          return false;
    
     ret = m_pickplace->setConfigName("/home/fshs/catkin_ws/src/hirop_pickandplace/hirop_PickPlace/config.yaml");
     std::cout<<"now pick running!!!"<<ret<<std::endl;
     if(m_pickplace->pickPlaceRun(_pickPos, _placePos))
     {
         res.isPickFinsh = true;
         return true;
     }
     else
     {
         std::cout<<"false"<<std::endl;
         res.isPickFinsh = false;
         return false;
     }
     
 }

 bool PickPlaceService::stop_callback(pick_place_bridge::ros_stop::Request &req, pick_place_bridge::ros_stop::Response &res)
 {
     int ret = m_pickplace->stop();
     return true;
 }

 bool PickPlaceService::freeback_callback(pick_place_bridge::ros_freeback::Request &req, pick_place_bridge::ros_freeback::Response &res)
 {
     std::string status;
     int ret = m_pickplace->freeback(status);
     res.status = status;
     return true; 
 }
