#ifndef IPICKPLACE_H
#define IPICKPLACE_H

#include "pickandplac.h"
#include "3rd/include/hplugin.h"
#include "geometry_msgs/Pose.h"

namespace hirop_pickPlace {

class IPickPlace{
public:
    /**
     * @brief 设置抓取点位
     * @param 传入，抓取点位
     * @return 0，成功  -1，失败
     */
    virtual int set_pick_poses(pose_vec pickPos) = 0;

    /**
     * @brief 设置放置点位
     * @param 传入，放置点位
     * @return 0，成功  -1，失败
     */
    virtual int set_place_poses(pose_vec placePos) = 0;

    /**
     * @brief 设置放置的目标点位
     * @return 0，成功  -1，失败
     */
    virtual int set_object(geometry_msgs::Pose) = 0;

    /**
     * @brief 抓取实现
     * @return 0，成功  -1，失败
     */
    virtual int pick() = 0;

    /**
     * @brief 放置实现
     * @return 0，成功  -1，失败
     */
    virtual int place() = 0;

    /**
     * @brief 获取执行器状态
     * @param 传出，状态
     * @return 0，成功  -1，失败
     */
    virtual int pickplace_freeback(std::string &status) = 0;

    /**
     * @brief 执行器停止
     * @return 0，成功  -1，失败
     */
    virtual int stop_pickplace() = 0;

    virtual int getName(std::string &name) = 0;

    virtual ENTITY_TYPE getEntityType() = 0;

    virtual ~IPickPlace(){}

protected:
    // 保存器的字符描述
    std::string name;

    // 其算法实现类别 C++ / Python
    hirop_pickPlace::ENTITY_TYPE entityType;
};

}
H_DECLARE_INTERFACE(hirop_pickPlace::IPickPlace,"IPickPlace/v1.0")
#endif // IPICKPLACE_H
