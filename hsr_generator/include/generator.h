#ifndef POSES_BUILDER_H
#define POSES_BUILDER_H
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <geometry_msgs/Pose.h>
#include "igenerator.h"
#include "c_base_generator.h"
#include "3rd/include/hpluginloader.h"
#include <tf/transform_datatypes.h>
#include <tf/tf.h>

#define PI  3.14159265358979323846   // pi

using namespace hirop_pickPlace;
class hsr_generator:public CBaseGenerator{
public:

    /**
     * @brief 构造函数
     */
    hsr_generator();

    /**
     * @brief 析构函数
     */
    ~hsr_generator();

    /**
     * @brief 设置抓取位姿
     * @return 1 成功， -1 失败
     */
    int set_pick_pose(geometry_msgs::Pose) ;

    /**
     * @brief 设置放置位姿
     * @return 0 成功， -1 失败
     */
    int set_place_pose(geometry_msgs::Pose) ;

    /**
     * @brief 执行生成抓取点位操作
     * @return 1 成功， -1 失败
     */
    int gen_pick_pose() ;

    /**
     * @brief 执行生成放置点位操作
     * @return 0成功， -1 失败
     */
    int gen_place_pose() ;

    /**
     * @brief 获取抓取和放置点位
     * @param 传出， 抓取点位
     * @param 传出， 放置点位
     * @return 0 成功， -1 失败
     */
    int getResult(pose_vec &pickPoses, pose_vec &placePoses,geometry_msgs::Pose &object_pose);

    /**
     * @brief 停止生成点位
     * @return 0 成功， -1 失败
     */
    int stop_generator() ;

    /**
     * @brief 返回生成进度
     */
    int generator_freeback(std::string &status);

private:
    /**
     * @brief 修正欧拉角
     * @param euler，输入输出，欧拉角
     * @return 0
     */
    int correct_euler(euler origin,euler &out_euler);

    /**
     * @brief 生成抓取进给方向
     * @param 输出，方向
     * @return 0
     */
    int get_pick_diraction(euler &pick_euler,pick_vect &vect,std::vector<quaternion> &quats);

    /**
     * @brief 四元数转欧拉角
     * @param 输入欧拉角
     * @param 输出四元数
     * @return 0 成功， -1 失败
     */
    int quaternion_to_euler(quaternion quat,euler &pick_euler);

    /**
     * @brief 欧拉角转四元素
     * @param euler_angle，输入欧拉角
     * @param quat ，输出，四元素
     * @return 0
     */
    int euler_to_quaternion(euler euler_angle, quaternion &quat);

    /**
     * @brief make_more_pick
     * @return
     */
    int make_more_pick(move_euler mev,euler euler_angle,std::vector<quaternion> &quats);

private:
   pickandplace_pose _pickpose;
   pickandplace_pose _placepose;
   geometry_msgs::Pose _objectpose;
   pose_vec _pickposes;
   pose_vec _placeposes;
   euler _pick_euler;
   quaternion _pick_quat;
   std::string _status;
   pick_vect _vectxyz;

};

H_DECLARE_PLUGIN(IGenerator)
#endif // POSES_BUILDER_H
