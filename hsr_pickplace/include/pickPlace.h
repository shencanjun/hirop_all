#ifndef PICK_EXCUTE_H
#define PICK_EXCUTE_H
#include <string>
#include <ros/ros.h>
#include <moveit_msgs/Grasp.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>
#include <geometry_msgs/PoseStamped.h>
#include <moveit_msgs/GripperTranslation.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/MoveItErrorCodes.h>
#include <tf2/LinearMath/Quaternion.h>

#include "hsr_gripper_driver/open_srv.h"
#include <sstream>

#include "pickPlace_execute.h"
#include "c_base_pickPlace.h"
#include "3rd/include/hpluginloader.h"

#define REFERENCE_FRAME "base_link"
#define PLANNER_ID "RRTstarkConfigDefault"

using namespace hirop_pickPlace;
class hsr_pickplace:public CBasePickPlace{
public:
    hsr_pickplace();

    int set_pick_poses(pose_vec pickPos);

    int set_place_poses(pose_vec placePos);

    int set_object(geometry_msgs::Pose object_pose);

    int pick() ;

    int place() ;

    int pickplace_freeback(std::string &status);

    int stop_pickplace() ;

private:

    int _init();

    int move_to_home();

    int make_grasp();

    int moveit_init();

    int add_collision_object(std::string object_id);

    int add_base_table();

    int add_collision();

    int remove_collision();

    int attach_collision(std::string obj);

    int dettach_collision(std::string obj);

    trajectory_msgs::JointTrajectory make_gripper_posture(double jiont_position);

    int gripper_open(int speed);

private:
    ros::NodeHandle npick;
    pickandplace_pose _pickpose;
    pickandplace_pose _placepose;
    pose_vec _pickposes;
    pose_vec _placeposes;
    bool _pick_stop_flag;
    std::string _status;
    std::vector<moveit_msgs::Grasp> _grasp_poses;
    std::vector<moveit_msgs::CollisionObject> _collision_objects;
    moveit::planning_interface::MoveGroup  *_move_group;
    moveit::planning_interface::PlanningSceneInterface _plan_Scene;
    tf2::Quaternion _orientation;
    std::vector<std::string> _object_ids;
    geometry_msgs::Pose _box_pose;
    const std::string _enf_link;
};
H_DECLARE_PLUGIN(hirop_pickPlace::IPickPlace)
#endif // PICK_EXCUTE_H
