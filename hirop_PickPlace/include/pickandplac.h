#ifndef PICKANDPLAC_H
#define PICKANDPLAC_H
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

namespace hirop_pickPlace {

enum ENTITY_TYPE{
    PYTHON = 0,
    CPP
};

//欧拉角结构体
typedef struct euler{
    double roll;
    double pitch;
    double yaw;
}euler;

//四元数结构体
typedef struct quaternion{
    double x;
    double y;
    double z;
    double w;
} quaternion;

//位置结构体
typedef struct position{
    double x;
    double y;
    double z;
} position;

//抓取进给距离结构体
typedef struct pick_dist{
    double pre_dist_min;
    double pre_dist_max;
    double dist_min;
    double dist_max;
}pick_dist;

//抓取进给方向结构体
typedef struct pick_vect{
    double vect_x;
    double vect_y;
    double vect_z;
}pick_vect;

enum move_euler{
    R = 0,
    P,
    Y,
};

//抓取数据结构体
typedef struct pickandplace_pose{
    move_euler m_euler;
    struct position position;
    struct quaternion quaternion;
    struct euler euler;
    struct pick_vect vect;
    struct pick_vect pre_vect;
    struct pick_dist dist;
}pickandplace_pose;

/**
 * @brief 用于传递的抓取数据结构体
 */
typedef std::vector<pickandplace_pose> pose_vec;

}
#endif // PICKANDPLAC_H
