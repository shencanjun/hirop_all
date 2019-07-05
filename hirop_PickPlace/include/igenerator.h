#ifndef IPOSES_BUILDER_H
#define IPOSES_BUILDER_H

#include "pickandplac.h"
#include "3rd/include/hplugin.h"
#include "geometry_msgs/Pose.h"

namespace hirop_pickPlace{

class IGenerator{

public:

    /**
     * @brief 设置抓取的目标点位
     * @return  0，成功  -1，失败
     */
    virtual int set_pick_pose(geometry_msgs::Pose)  = 0;

    /**
     * @brief 设置放置的目标点位
     * @return 0，成功  -1，失败
     */
    virtual int set_place_pose(geometry_msgs::Pose) = 0;

    /**
     * @brief 生成抓取的目标点位
     * @return 0，成功  -1，失败
     */
    virtual int gen_pick_pose() = 0;

    /**
     * @brief 生成放置的目标点位
     * @return 0，成功  -1，失败
     */
    virtual int gen_place_pose() = 0;

    /**
     * @brief 获取生成后的抓取和放置目标点位
     * @param 传出，抓取目标点位
     * @param 传出，放置目标点位
     * @return 0，成功  -1，失败
     */
    virtual int getResult(pose_vec &pickPoses, pose_vec &placePoses,geometry_msgs::Pose &object_pose)= 0;

    /**
     * @brief 停止生成
     * @return 0，成功  -1，失败
     */
    virtual int stop_generator() = 0;

    /**
     * @brief 获取生成器状态
     * @param 传出，状态
     * @return 0，成功  -1，失败
     */
    virtual int generator_freeback(std::string &status) = 0;

    virtual int getName(std::string &name) = 0;

    virtual ENTITY_TYPE getEntityType() = 0;

     virtual ~IGenerator(){}

protected:
    // 保存识别器的字符描述
    std::string name;

    // 其算法实现类别 C++ / Python
    hirop_pickPlace::ENTITY_TYPE entityType;

};
}
H_DECLARE_INTERFACE(hirop_pickPlace::IGenerator,"IGenerator/v1.0")


#endif // IPOSES_BUILDER_H
