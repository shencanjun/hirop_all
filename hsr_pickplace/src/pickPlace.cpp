#include "pickPlace.h"

using namespace hirop_pickPlace;

hsr_pickplace::hsr_pickplace()
{
    _init();
}

int hsr_pickplace::_init()
{
     remove_collision();
     add_base_table();
     _pick_stop_flag = false;
     _status = "pick_now";
     return 0;
}

int hsr_pickplace::moveit_init()
{
    _move_group = new moveit::planning_interface::MoveGroup("arm");
    _move_group->setPoseReferenceFrame("base_link");
    return 0;
}

int hsr_pickplace::set_pick_poses(pose_vec pickPos)
{
    _status = "set_pick_poses";
    _pickposes = pickPos;
    _status = 1;
    _pickpose = pickPos[0];
    std::cout<<"_pickposes.px ="<<_pickpose.position.x;
    std::cout<<"_pickposes.py ="<<_pickpose.position.y;
    std::cout<<"_pickposes.pz ="<<_pickpose.position.z;
    return 0;
}

int hsr_pickplace::set_place_poses(pose_vec placePos)
{
    _status = "set_place_poses";
    _placeposes = placePos;
    _placepose = placePos[0];
    std::cout<<"_placeposes.px ="<<_placepose.position.x;
    std::cout<<"_placeposes.py ="<<_placepose.position.y;
    std::cout<<"_placeposes.pz ="<<_placepose.position.z;
    _status = 1;
    return 0;
}

int hsr_pickplace::set_object(geometry_msgs::Pose object_pose)
{
    _box_pose = object_pose;
    return 0;
}

int hsr_pickplace::add_collision_object(std::string object_id)
{
    shape_msgs::SolidPrimitive primitive;
    moveit_msgs::CollisionObject collision_object;
    collision_object.header.frame_id = "base_link";
    _status = 20;
    collision_object.id = object_id;
    _object_ids.push_back(collision_object.id);
    primitive.type = primitive.BOX;
    primitive.dimensions.resize(3);
    primitive.dimensions[0] = 0.055;
    primitive.dimensions[1] = 0.055;
    primitive.dimensions[2] = 0.11;
    collision_object.primitives.push_back(primitive);
    collision_object.primitive_poses.push_back(_box_pose);
    collision_object.operation = collision_object.ADD;

    _collision_objects.push_back(collision_object);

    return 0;
}

int hsr_pickplace::add_base_table()
{
    _status = "add_base_table";
    shape_msgs::SolidPrimitive primitive;
    moveit_msgs::CollisionObject collision_object;
    geometry_msgs::Pose base_pose;
    std::vector<moveit_msgs::CollisionObject> ob;
    collision_object.header.frame_id = "base_link";
    _status = 15;
    collision_object.id = "base_table";
    _object_ids.push_back(collision_object.id);
    primitive.type = primitive.BOX;
    primitive.dimensions.resize(3);
    primitive.dimensions[0] = 3;
    primitive.dimensions[1] = 3;
    primitive.dimensions[2] = 0.025;
    collision_object.primitives.push_back(primitive);
    base_pose.position.x = 0;
    base_pose.position.y = 0;
    base_pose.position.z = -0.25;
    base_pose.orientation.w = 1;
    collision_object.primitive_poses.push_back(base_pose);
    collision_object.operation = collision_object.ADD;
    ob.push_back(collision_object);
    //_collision_objects.push_back(collision_object);
    _plan_Scene.addCollisionObjects(ob);
    std::cout<<"add base_table";
    sleep(1.0);
    return 0;
}

int hsr_pickplace::add_collision()
{
    _status = "add_collision";
    _plan_Scene.addCollisionObjects(_collision_objects);
    sleep(0.8);
    _collision_objects.clear();
    _status = 20;
    std::cout<<"add_collision"<<std::endl;
    return 0;
}

int hsr_pickplace::remove_collision()
{
    _plan_Scene.removeCollisionObjects(_object_ids);
    _object_ids.clear();
    return 0;
}

int hsr_pickplace::attach_collision(std::string obj)
{
    _move_group->attachObject(obj);
    return 0;
}

int hsr_pickplace::dettach_collision(std::string obj)
{
    std::vector<std::string> det_obj;
    det_obj.push_back(obj);
    _move_group->detachObject(obj);
    sleep(1.0);
    _plan_Scene.removeCollisionObjects(det_obj);
    sleep(0.5);
    det_obj.clear();
    return 0;
}

trajectory_msgs::JointTrajectory hsr_pickplace::make_gripper_posture(double jiont_position)
{
    trajectory_msgs::JointTrajectory tj;
    trajectory_msgs::JointTrajectoryPoint tjp;
    tj.joint_names.push_back("right_finger_2_joint");
    tjp.positions.push_back(jiont_position);
    tjp.effort.push_back(1.0);
    tjp.time_from_start = ros::Duration(1.0);
    tj.points.push_back(tjp);
    return tj;
}

int hsr_pickplace::make_grasp()
{
    _status = "make_grasp start";
    _status = 50;
    moveit_msgs::Grasp grasp_pose;
    tf2::Quaternion orien;
    _grasp_poses.clear();
    grasp_pose.grasp_pose.header.frame_id = "base_link";

    _move_group = new moveit::planning_interface::MoveGroup("arm");
    //geometry_msgs::PoseStamped t1 = _move_group->getCurrentPose();

    //抓取前位置
    grasp_pose.pre_grasp_approach.direction.header.frame_id = "base_link";
    grasp_pose.pre_grasp_approach.direction.vector.x = _pickpose.pre_vect.vect_x;
    grasp_pose.pre_grasp_approach.direction.vector.y = _pickpose.pre_vect.vect_y;
    grasp_pose.pre_grasp_approach.direction.vector.z = _pickpose.pre_vect.vect_z;
    grasp_pose.pre_grasp_approach.min_distance = _pickpose.dist.pre_dist_min;
    grasp_pose.pre_grasp_approach.desired_distance = _pickpose.dist.pre_dist_max;

    //抓取后的位置
    grasp_pose.post_grasp_retreat.direction.header.frame_id = "base_link";
    grasp_pose.post_grasp_retreat.direction.vector.x = _pickpose.vect.vect_x;
    grasp_pose.post_grasp_retreat.direction.vector.y = _pickpose.vect.vect_y;
    grasp_pose.post_grasp_retreat.direction.vector.z = _pickpose.vect.vect_z;
    grasp_pose.post_grasp_retreat.min_distance = _pickpose.dist.dist_min;
    grasp_pose.post_grasp_retreat.desired_distance = _pickpose.dist.dist_max;

    std::stringstream ss;

    for(int i = 0; i<_pickposes.size();i++)
    {
        ss.clear();
       // orien.setRPY(_pickpose.euler.roll,_pickpose.euler.pitch,_pickpose.euler.yaw);
    //             //抓取位置
        grasp_pose.allowed_touch_objects.push_back("objiect"); 
        grasp_pose.max_contact_force = 0;
        grasp_pose.pre_grasp_posture = make_gripper_posture(0.0);
        grasp_pose.grasp_posture = make_gripper_posture(-0.3491);
        grasp_pose.grasp_pose.pose.orientation.w = _pickposes[i].quaternion.w;
        grasp_pose.grasp_pose.pose.orientation.x = _pickposes[i].quaternion.x;
        grasp_pose.grasp_pose.pose.orientation.y = _pickposes[i].quaternion.y;
        grasp_pose.grasp_pose.pose.orientation.z = _pickposes[i].quaternion.z;
        grasp_pose.grasp_pose.pose.position.x = _pickposes[i].position.x;
        grasp_pose.grasp_pose.pose.position.y = _pickposes[i].position.y;
        grasp_pose.grasp_pose.pose.position.z = _pickposes[i].position.z;
        ss<<i;
        grasp_pose.id = ss.str();
        _grasp_poses.push_back(grasp_pose);
    }

    // if(_pickpose.m_euler == P)
    // {
    //     for(int p = 0;p <5; p++)
    //     {
    //             orien.setRPY(_pickpose.euler.roll,p_val[p],_pickpose.euler.yaw);
    //             //抓取位置
    //             grasp_pose.allowed_touch_objects.push_back("objiect");
    //             grasp_pose.max_contact_force = 0;
    //             grasp_pose.pre_grasp_posture = make_gripper_posture(0.0);
    //             grasp_pose.grasp_posture = make_gripper_posture(-0.3491);
    //             // grasp_pose.grasp_pose.pose.orientation.w = _pickpose.quaternion.w;
    //             // grasp_pose.grasp_pose.pose.orientation.x = _pickpose.quaternion.x;
    //             // grasp_pose.grasp_pose.pose.orientation.y = _pickpose.quaternion.y;
    //             // grasp_pose.grasp_pose.pose.orientation.z = _pickpose.quaternion.z;
    //             grasp_pose.grasp_pose.pose.position.x = _pickpose.position.x;
    //             grasp_pose.grasp_pose.pose.position.y = _pickpose.position.y;
    //             grasp_pose.grasp_pose.pose.position.z = _pickpose.position.z;
    //             ss<<"p"<<p;
    //             grasp_pose.id = ss.str() ;
    //             _grasp_poses.push_back(grasp_pose);
    //     }
    // }

//     if(_pickpose.m_euler == Y)
//     {
//         for(int y = 0;y <5; y++)
//         {
//             orien.setRPY(_pickpose.euler.roll,_pickpose.euler.pitch,y_val[y]);
//                 //抓取位置
//                 grasp_pose.allowed_touch_objects.push_back("objiect");
//                 grasp_pose.max_contact_force = 0;
//                 grasp_pose.pre_grasp_posture = make_gripper_posture(0.0);
//                 grasp_pose.grasp_posture = make_gripper_posture(-0.3491);
//                 // grasp_pose.grasp_pose.pose.orientation.w = _pickpose.quaternion.w;
//                 // grasp_pose.grasp_pose.pose.orientation.x = _pickpose.quaternion.x;
//                 // grasp_pose.grasp_pose.pose.orientation.y = _pickpose.quaternion.y;
//                 // grasp_pose.grasp_pose.pose.orientation.z = _pickpose.quaternion.z;
//                 grasp_pose.grasp_pose.pose.position.x = _pickpose.position.x;
//                 grasp_pose.grasp_pose.pose.position.y = _pickpose.position.y;
//                 grasp_pose.grasp_pose.pose.position.z = _pickpose.position.z;
//                 //grasp_pose.id = "0" ;
//                 ss<<"y"<<y;
//                 grasp_pose.id = ss.str() ;
//                 _grasp_poses.push_back(grasp_pose);
//         }
//     }
    _status = "make_grasp finish";

    return 0;
}


int hsr_pickplace::pick()
{
    moveit_init();
    _pick_stop_flag = false;
    _status = "pick start";
    add_base_table();
    sleep(1.0);
    move_to_home();
    std::cout<<"pick start!!!!!"<<std::endl;
    make_grasp();

    //_move_group = new moveit::planning_interface::MoveGroup("arm");
    //_move_group->setPoseReferenceFrame("base_link");
    ros::AsyncSpinner spinner(1);
    spinner.start();

     _status = 60;
    int count = 0;
    bool result = false;
    add_collision_object("objiect");
    add_collision();
    std::cout<<"pick ready!!!!!"<<std::endl;
    
    while(count < _grasp_poses.size() && result == 0)
    {
         if(_pick_stop_flag)
             return -1;
         std::cout<<"count = "<<count<<std::endl;
         result = _move_group->pick("objiect",_grasp_poses);
         count ++;
         std::cout<<"result = "<<result<<std::endl;
         sleep(0.5);
    }
    _status = "pick finish";
    if(!result)
        return -1;  
    _status = 80;
    return 0;
}

int hsr_pickplace::move_to_home()
{
    if(_pick_stop_flag)
        return -1;
    _status = "move_to_home start";

    _move_group = new moveit::planning_interface::MoveGroup("arm");
    _move_group->setPoseReferenceFrame("base_link");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    

   _move_group->setNamedTarget("home");
   bool result = _move_group->move();
   sleep(1.0);
   std::cout<<"move to home result = "<<result<<std::endl;
   _status = "move_to_home finish";
   return 0;
}

int hsr_pickplace::place()
{
    moveit_init();
    if(_pick_stop_flag)
        return -1;
    _status = "place start";
    _status = 81;
    int count = 0;
    bool result;

    _move_group = new moveit::planning_interface::MoveGroup("arm");
    _move_group->setPoseReferenceFrame("base_link");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    
    geometry_msgs::Pose  placepose;
    moveit::planning_interface::MoveGroup::Plan my_plan;
    placepose.position.x = _placepose.position.x;
    placepose.position.y = _placepose.position.y;
    placepose.position.z = _placepose.position.z;
    placepose.orientation.w = _placepose.quaternion.w;
    placepose.orientation.x = _placepose.quaternion.x;
    placepose.orientation.y =_placepose.quaternion.y;
    placepose.orientation.z = _placepose.quaternion.z;

    _move_group->setPoseTarget(placepose);

    while(count < 3 && result == 0)
    {
        if(_pick_stop_flag)
            return -1;
        count  ++;
        std::cout<<"count = " <<count <<std::endl;
        result = _move_group->move();
        sleep(1.0);           
    }
    sleep(1.0);
    dettach_collision("objiect");
    //sleep(1.0);
    gripper_open(500);
    sleep(1.5);
    move_to_home();
    sleep(1.0);
    if(!result)
       return -1; 
    remove_collision();
    _status = "place finish";
    return 0;
}

int hsr_pickplace::pickplace_freeback(std::string &status)
{
    status = _status;
    return 0;
}

int hsr_pickplace::stop_pickplace()
{
    _pick_stop_flag = true;
    sleep(3.0);
    dettach_collision("objiect");
    sleep(1.0);
    remove_collision();
    _status = "pick_stop";
    return 0;
}

int hsr_pickplace::gripper_open(int speed)
{
	ros::ServiceClient client_gripperOpen = npick.serviceClient<hsr_gripper_driver::open_srv>("gripper_open");
    hsr_gripper_driver::open_srv gripperOpen_srv;
	gripperOpen_srv.request.speed = speed;
	if(client_gripperOpen.call(gripperOpen_srv))
	{
		std::cout<<"Open the Gripper sucessful!!!"<<std::endl;
	}
	else
	{
		std::cout<<"Open the Gripper failed!!!"<<std::endl;
	}	
}

 H_EXPORT_PLUGIN(hsr_pickplace, "hsr_pickplace", "1.0")

