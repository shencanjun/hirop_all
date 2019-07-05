#ifndef PICK_EXCUTE_H
#define PICK_EXCUTE_H
#include <string>
#include "configuer.h"
#include "pickandplac.h"
#include"igenerator.h"
#include "ipickPlace.h"
#include "cpp_loader.h"
#include<geometry_msgs/Pose.h>

namespace hirop_pickPlace {
class PickPlace{
public:

    /**
     * @brief 构造函数
     */
    PickPlace();

    /**
     * @brief 析构函数
     */
    ~PickPlace();

    /**
     * @brief 设置配置文件
     * @param 传入，配置文件名，包含路径
     * @return 0，成功  -1，失败
     */
    int setConfigName(std::string fileName);

    /**
     * @brief 抓取和放置操作
     * @param 传入，抓取位置
     * @param 传入，防止位置
     * @return 0，成功  -1，失败
     */
    int pickPlaceRun(geometry_msgs::Pose pickPos,geometry_msgs::Pose placePos);

    /**
     * @brief 返回执行状态
     * @return 0，成功  -1，失败
     */
    int freeback(std::string &status);

    /**
     * @brief 停止操作
     * @return  0，成功  -1，失败
     */
    int stop();

private:

    /**
     * @brief 设置生成器
     * @return  0，成功  -1，失败
     */
    int _setGeneratorConfig();

    /**
     * @brief 设置执行器
     * @return  0，成功  -1，失败
     */
    int _setPickPlaceConfig();

    /**
     * @brief 具体抓取实现
     * @param 传入，抓取位置
     * @return 0，成功  -1，失败
     */
    int _pick(pose_vec pickPos);

    /**
     * @brief 具体放置实现
     * @param 传入，放置位置
     * @return 0，成功  -1，失败
     */
    int _place(pose_vec placePos);

    /**
     * @brief 生成可用的抓取放置位置
     * @param 传入，抓取位置
     * @param 传入，放置位置
     * @return
     */
    int _gen_pick_place(geometry_msgs::Pose pickPos,geometry_msgs::Pose placePos);

private:
    /**
     * @brief 加载器
     */
    CppLoader *cload;

    /**
     * @brief 具体的生成器
     */
    IGenerator *generator;

    /**
     * @brief 具体的执行器
     */
    IPickPlace *pickplace;

    /**
     * @brief 具体的配置器
     */
    Configure *configuer;

    bool _stop_flag;
};
}
#endif // PICK_EXCUTE_H
