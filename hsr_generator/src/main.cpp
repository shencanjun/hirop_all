#include <iostream>
#include "include/generator.h"

using namespace std;
using namespace hirop_pickPlace;

int main()
{
    geometry_msgs::Pose pick;
    pose_vec pick_p,place;
  //  pick.header.frame_id = "base_link";
    pick.position.x = 0.8;
    pick.position.y = 0.6;
    pick.position.z = 0.85;
    pick.orientation.w = 0;
    pick.orientation.x = -0.50;
    pick.orientation.y =0.7;
    pick.orientation.z = -0.8;
    Generator *gen = new Generator();
    gen->set_pick_pose(pick);
    gen->set_place_pose(pick);
    gen->gen_pick_pose();
    gen->gen_place_pose();
    gen->getResult(pick_p,place);
    for(int i =0;i<pick_p.size();i++)
    {
        cout<<"Gpose.pose.x = "<<pick_p[i].position.x<<endl;
        cout<<"Gpose.pose.y = "<<pick_p[i].position.y<<endl;
        cout<<"Gpose.pose.z = "<<pick_p[i].position.z<<endl;
        cout<<"Gpose.orientation.x = "<<pick_p[i].quaternion.x<<endl;
        cout<<"Gpose.orientation.y = "<<pick_p[i].quaternion.y<<endl;
        cout<<"Gpose.orientation.z = "<<pick_p[i].quaternion.z<<endl;
        cout<<"Gpose.orientation.w = "<<pick_p[i].quaternion.w<<endl;
        cout<<"Gpose.vect.vect_x = "<<pick_p[i].vect.vect_x<<endl;
        cout<<"Gpose.vect.vect_y = "<<pick_p[i].vect.vect_y<<endl;
        cout<<"Gpose.vect.vect_z = "<<pick_p[i].vect.vect_z<<endl;
        cout<<"Gpose.pre_vect.vect_x = "<<pick_p[i].pre_vect.vect_x<<endl;
        cout<<"Gpose.pre_vect.vect_y = "<<pick_p[i].pre_vect.vect_y<<endl;
        cout<<"Gpose.pre_vect.vect_z = "<<pick_p[i].pre_vect.vect_z<<endl;
        cout<<"Gpose.euler.Pitch= "<<pick_p[i].euler.pitch<<endl;
        cout<<"Gpose.euler.Roll = "<<pick_p[i].euler.roll<<endl;
        cout<<"Gpose.euler.Yaw = "<<pick_p[i].euler.yaw<<endl;
        cout<<"Gpose.dist_max = "<<pick_p[i].dist.dist_max<<endl;
        cout<<"Gpose.dist_min = "<<pick_p[i].dist.dist_min<<endl;
        cout<<"Gpose.pre_dist_min = "<<pick_p[i].dist.pre_dist_min<<endl;
        cout<<"Gpose.pre_dist_max = "<<pick_p[i].dist.pre_dist_max<<endl;

        cout<<"place.pose.x = "<<place[i].position.x<<endl;
        cout<<"place.pose.y = "<<place[i].position.y<<endl;
        cout<<"place.pose.z = "<<place[i].position.z<<endl;
        cout<<"place.orientation.x = "<<place[i].quaternion.x<<endl;
        cout<<"place.orientation.y = "<<place[i].quaternion.y<<endl;
        cout<<"place.orientation.z = "<<place[i].quaternion.z<<endl;
        cout<<"place.orientation.w = "<<place[i].quaternion.w<<endl;
        cout<<"place.vect.vect_x = "<<place[i].vect.vect_x<<endl;
        cout<<"place.vect.vect_y = "<<place[i].vect.vect_y<<endl;
        cout<<"place.vect.vect_z = "<<place[i].vect.vect_z<<endl;
        cout<<"place.euler.Pitch= "<<place[i].euler.pitch<<endl;
        cout<<"place.euler.Roll = "<<place[i].euler.roll<<endl;
        cout<<"place.euler.Yaw = "<<place[i].euler.yaw<<endl;
        cout<<"place.dist_max = "<<place[i].dist.dist_max<<endl;
        cout<<"place.dist_min = "<<place[i].dist.dist_min<<endl;
        cout<<"place.pre_dist_min = "<<place[i].dist.pre_dist_min<<endl;
        cout<<"place.pre_dist_max = "<<place[i].dist.pre_dist_max<<endl;
    }
    cout << "Hello World!" << endl;
    return 0;
}

