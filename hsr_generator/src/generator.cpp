#include"include/generator.h"

using namespace hirop_pickPlace;

hsr_generator::hsr_generator()
{
    _status = "ready";
}

hsr_generator::~hsr_generator()
{

}

int hsr_generator::set_pick_pose(geometry_msgs::Pose pickPose)
{
      _pickpose.position.x  = pickPose.position.x;
     _pickpose.position.y  = pickPose.position.y;
      _pickpose.position.z  = pickPose.position.z;
      _pickpose.quaternion.x  = pickPose.orientation.x;
      _pickpose.quaternion.y  = pickPose.orientation.y;
      _pickpose.quaternion.z  = pickPose.orientation.z;
      _pickpose.quaternion.w  = pickPose.orientation.w;
      _objectpose = pickPose;
      _status = "set_pick_pose";
      return 0;
}

int hsr_generator::set_place_pose(geometry_msgs::Pose placePose)
{
      _placepose.position.x  = placePose.position.x;
      _placepose.position.y  = placePose.position.y;
      _placepose.position.z  = placePose.position.z;
      _placepose.quaternion.x  = placePose.orientation.x;
      _placepose.quaternion.y  = placePose.orientation.y;
      _placepose.quaternion.z  = placePose.orientation.z;
      _placepose.quaternion.w  = placePose.orientation.w;
      _status = "set_place_pose";
      return 0;
}

int hsr_generator::gen_pick_pose()
{
    _status = "gen_pick_pose start";
    pick_vect vect;
    euler con_euler,pick_euler;
    move_euler me;
    quaternion quat;
    std::vector<quaternion> quats;

    quaternion_to_euler(_pickpose.quaternion, con_euler);
    std::cout<<"con_euler_r:"<<con_euler.roll<<std::endl;
    std::cout<<"con_euler_y:"<<con_euler.yaw<<std::endl;
    std::cout<<"con_euler_p:"<<con_euler.pitch<<std::endl;

    correct_euler(con_euler,pick_euler);
    get_pick_diraction(pick_euler,vect,quats);
    euler_to_quaternion(pick_euler,quat);
    std::cout<<"conver_quat_x:"<<quat.x<<std::endl;
    std::cout<<"conver_quat_y:"<<quat.y<<std::endl;
    std::cout<<"conver_quat_z:"<<quat.z<<std::endl;
    std::cout<<"conver_quat_w:"<<quat.w<<std::endl;

    _objectpose.orientation.w = quat.w;
    _objectpose.orientation.x = quat.x;
    _objectpose.orientation.y = quat.y;
    _objectpose.orientation.z = quat.z;
    std::cout<<"quats.size = "<<quats.size()<<std::endl;
    for(int i = 0; i < quats.size(); i++)
    {
        _pickpose.quaternion = quats[i];
        _pickpose.m_euler = me;
        _pickpose.euler = pick_euler;

        _pickpose.pre_vect = vect;

        _pickpose.vect.vect_x = 0;
        _pickpose.vect.vect_y = 0;
        _pickpose.vect.vect_z = 1.7;

        _pickpose.dist.pre_dist_min = 0.01;
        _pickpose.dist.pre_dist_max = 0.1;
        _pickpose.dist.dist_min = 0.01;
        _pickpose.dist.dist_max = 0.1;
        _pickposes.push_back(_pickpose);
    }
    _status = "gen_pick_pose finished";
    return 0;
}

int hsr_generator::gen_place_pose()
{
    _status = " start";
    _placeposes.push_back(_placepose);
    _status = "gen_place_pose finished";
    return 0;
}

int hsr_generator::generator_freeback(std::string &status)
{
    status = _status;
    return 0;
}

int hsr_generator::getResult(pose_vec &pickPoses, pose_vec &placePoses,geometry_msgs::Pose &object_pose)
{
    if(_pickposes.size()<=0||_placeposes.size()<=0)
        return -1;
    pickPoses = _pickposes;
    placePoses = _placeposes;
    object_pose = _objectpose;
    return 0;
}

int hsr_generator::stop_generator()
{
    _status = "stop_generator";
    return 0;
}

int hsr_generator::correct_euler(euler origin,euler &out_euler)
{
    std::cout<<"origin.r =" <<origin.roll <<std::endl;
    std::cout<<"origin.p =" <<origin.pitch <<std::endl;
    std::cout<<"origin.y =" <<origin.yaw <<std::endl;

    if(origin.pitch < -1.57)
        origin.pitch =origin.pitch + 3.14;
    if(origin.roll < -1.57)
        origin.roll =origin.roll + 3.14;
    if(origin.yaw < -1.57)
        origin.yaw =origin.yaw + 3.14;

    if(origin.pitch > 1.57)
        origin.pitch =origin.pitch - 3.14;
    if(origin.roll  > 1.57)
        origin.roll =origin.roll - 3.14;
    if(origin.yaw > 1.57)
        origin.yaw =origin.yaw - 3.14;

    out_euler.pitch = origin.pitch;
    out_euler.roll = origin.roll;
    out_euler.yaw = origin.yaw;

    std::cout<<"out_euler.r =" <<out_euler.roll <<std::endl;
    std::cout<<"out_euler.p =" <<out_euler.pitch <<std::endl;
    std::cout<<"out_euler.y =" <<out_euler.yaw <<std::endl;
    return 0;
}

int hsr_generator::get_pick_diraction(euler &pick_euler, pick_vect &vect,std::vector<quaternion> &quats)
{
    double neg_radian45 = -0.785398;
    double atv_radian45 = 0.785398;
    double neg_radian10 = -0.1745329;
    double atv_radian10 = 0.1745329;
    double neg_radian70 = -1.22173047;
    double atv_radian70 = 1.22173047;

    if((pick_euler.roll >= neg_radian45 && pick_euler.roll<= atv_radian45) && (pick_euler.pitch >= neg_radian45 && pick_euler.pitch<= atv_radian45))
    {
        if(pick_euler.yaw > 0 )
        {
            if(pick_euler.yaw > atv_radian45)
            {
                pick_euler.yaw += 1.57;
            }
        }
        else
        {
            if(pick_euler.yaw < neg_radian45)
            {
                pick_euler.yaw -= 1.57;
            }
        }
        if(pick_euler.yaw >= neg_radian10 && pick_euler.yaw <= atv_radian10||pick_euler.yaw <= neg_radian70 ||pick_euler.yaw >= atv_radian70)
        {
            vect.vect_x = 1;
            vect.vect_y = 0;
            vect.vect_z = 0;
            pick_euler.roll = 0;
            pick_euler.pitch = 0;
            pick_euler.yaw = 0;
            make_more_pick(P,pick_euler,quats);
        }
        else
        {
            if(pick_euler.yaw > 0)
            {
                vect.vect_x = fabs(sin(1.57-pick_euler.yaw));
            }
            else
            {
               vect.vect_x = fabs(sin(-1.57+pick_euler.yaw));
            }
            vect.vect_y = sin(pick_euler.yaw);
            vect.vect_z = 0;
            pick_euler.roll = 0;
            pick_euler.pitch = 0;
            make_more_pick(R,pick_euler,quats);
           // pick_euler.yaw = 0;
        }
    }
    else
    {
          vect.vect_x = 0;
          vect.vect_y = 0;
          vect.vect_z = -1;
          if(pick_euler.roll <= neg_radian45 || pick_euler.roll >= atv_radian45 || pick_euler.pitch <=neg_radian45 ||pick_euler.pitch >= atv_radian45)
          {
              pick_euler.yaw = 0;
              pick_euler.pitch = 1.57;
              //pick_euler.roll = 1.57;
          }
          make_more_pick(Y,pick_euler,quats);
    }
    std::cout<<"pick_euler.r =" <<pick_euler.roll <<std::endl;
    std::cout<<"pick_euler.p =" <<pick_euler.pitch <<std::endl;
    std::cout<<"pick_euler.y =" <<pick_euler.yaw <<std::endl;
    return 0;
}

 int hsr_generator::quaternion_to_euler(quaternion quat,euler &pick_euler)
 {
     tf::Quaternion quatt;
     quatt.setW(quat.w);
     quatt.setX(quat.x);
     quatt.setY(quat.y);
     quatt.setZ(quat.z);

     tf::Matrix3x3(quatt).getRPY(pick_euler.roll,pick_euler.pitch,pick_euler.yaw);

     return 0;
 }

 int hsr_generator::euler_to_quaternion(euler euler_angle, quaternion &quat)
 {

     tf::Quaternion tq;
     tq = tf::createQuaternionFromRPY(euler_angle.roll,euler_angle.pitch,euler_angle.yaw);

     quat.w = tq.w();
     quat.x = tq.x();
     quat.y = tq.y();
     quat.z = tq.z();
      return 0;
 }

int hsr_generator::make_more_pick(move_euler mev,euler euler_angle,std::vector<quaternion> &quats)
{
    double m_vals[7] = {0,0.1,-0.1,0.2,0.3,0.4,0.5};
    euler remake_euler;
    quaternion remake_quat;

        for(int i  = 0; i < 7; i++)
        {
            if(mev == P)
            {
                remake_euler.pitch = m_vals[i];
                remake_euler.roll = euler_angle.roll;
                remake_euler.yaw = euler_angle.yaw;
            }
            if(mev == R)
            {

                remake_euler.pitch = m_vals[i]*(remake_euler.yaw/1.57);
                remake_euler.roll = m_vals[i]*(1-(remake_euler.yaw/1.57));
                remake_euler.yaw = euler_angle.yaw;
            }
            if(mev == Y)
            {
                remake_euler.pitch = euler_angle.pitch;
                remake_euler.roll = euler_angle.roll;
                remake_euler.yaw = euler_angle.yaw;
            }

            euler_to_quaternion(remake_euler,remake_quat);

            quats.push_back(remake_quat);
        }

        return 0;
}

 H_EXPORT_PLUGIN(hsr_generator,  "hsr_generator",  "1.0")
