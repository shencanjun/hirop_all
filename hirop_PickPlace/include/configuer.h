#ifndef CONFIGUER_H
#define CONFIGUER_H
#include <iostream>
#include <stdio.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/parser.h"

#ifdef DEBUG
#define configDebug(format, ...)  printf("[debug ]: " #format "\n[detail]: File: %s, Line: %d, Function: %s \n",\
    ##__VA_ARGS__, __FILE__, __LINE__, __FUNCTION__);
#else
#define configDebug(format, ...)
#endif

namespace hirop_pickPlace {

class Configure{

public:
    /**
     * @brief 构造函数
     * @param [file] 输入， yaml配置文件名称
     */
    Configure(std::string fileName);

    /**
     * @brief       获取配置文件中的物体名称
     * @param    [objName] 输出， 物体名称
     * @return
     *          0 成功
     *          1 失败
     */
    int getObjectName(std::string &objName);

    /**
     * @brief       获取配置文件中生成器的名称
     * @param   [trainerName] 输出，生成器名称
     * @return
     *          0 成功
     *          1 失败
     */
    int getGeneratorName(std::string &generatorName);

    /**
     * @brief 获取配置文件中执行器的名称
     * @param 输出，执行器
     * @return
     */
    int getPickPlacerName(std::string &pickpalcerName);

    /**
     * @brief 获取文件中生成器的搜索路径
     * @param 输出，路径
     * @return
     */
    int getGeneratorPath(std::string &generatorPath);

    /**
     * @brief 获取配置文件中的执行器路径
     * @param 输出，路径
     * @return
     */
    int getPickPlacerPath(std::string &pickpalcerPath);

private:
    // 当前Configuere中的yaml配置文件实例
    YAML::Node config;

};

}
#endif // CONFIGUER_H
