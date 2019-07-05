#include"pickPlace_execute.h"

using namespace hirop_pickPlace;

PickPlace::PickPlace()
{
    _stop_flag = false;
}

PickPlace::~PickPlace()
{
    cload = NULL;
    generator = NULL;
    pickplace = NULL;
    configuer = NULL;

    delete cload;
    delete generator;
    delete pickplace;
    delete configuer;
}

int PickPlace::setConfigName(std::string fileName)
{
     std::cout<<"filename:"<<fileName<<std::endl;
     configuer = new Configure(fileName);
     _setGeneratorConfig();
     _setPickPlaceConfig();
     return 0;
}

int PickPlace::_setGeneratorConfig()
{
    std::string generatorName;
    std::string generatorPath;
    if(configuer == NULL)
        return -1;
    configuer->getGeneratorName(generatorName);
    configuer->getGeneratorPath(generatorPath);
    this->generator = cload->loadGenerator(generatorName,generatorPath);
   if(this->generator == NULL)
   {
       std::cerr<<"load Generator: error!"<<std::endl;
       return -1;
   }
   return 0;
}

int PickPlace::_setPickPlaceConfig()
{
    std::string pickPlaceName;
    std::string pickPlacePath;
   if(configuer == NULL)
       return -1;
    configuer->getPickPlacerName(pickPlaceName);
    configuer->getPickPlacerPath(pickPlacePath);
    //加载生成器
    this->pickplace = cload->loadPickPlace(pickPlaceName,pickPlacePath);
   if(this->pickplace == NULL)
   {
       std::cerr<<"load PickPlace: error!"<<std::endl;
       return -1;
   }
   return 0;
}

int PickPlace::pickPlaceRun(geometry_msgs::Pose pickPos, geometry_msgs::Pose placePos)
{
    _stop_flag = false;
    if(this->generator == NULL)
    {
        std::cerr<<"generation:error!!!"<<std::endl;
        return -1;
    }
    if(this->pickplace == NULL)
    {
        std::cerr<<"pickplace: error!!!"<<std::endl;
        return -1;
    }

   std::cerr<<"ready!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    pose_vec pickPoss,placePoss;
    geometry_msgs::Pose objectPose;

    this->_gen_pick_place(pickPos,placePos);

    this->generator->getResult(pickPoss, placePoss,objectPose);

    if(pickPoss.size()<=0)
    {
        std::cout<<"pickposes have not vlaue!!!"<<std::endl;
       return -1;
    }

    for(int i = 0;i<pickPoss.size();i++)
    {
        std::cout<<"pickPoss.px = "<<pickPoss[0].position.x<<std::endl;
        std::cout<<"pickPoss.py = "<<pickPoss[0].position.y<<std::endl;
        std::cout<<"pickPoss.pz = "<<pickPoss[0].position.z<<std::endl;
        std::cout<<"pickPoss.ox = "<<pickPoss[0].quaternion.x<<std::endl;
        std::cout<<"pickPoss.oy = "<<pickPoss[0].quaternion.y<<std::endl;
        std::cout<<"pickPoss.oz = "<<pickPoss[0].quaternion.z<<std::endl;
        std::cout<<"pickPoss.ow = "<<pickPoss[0].quaternion.w<<std::endl;
        std::cout<<"pickPoss.pre_vect.x = "<<pickPoss[0].pre_vect.vect_x<<std::endl;
        std::cout<<"pickPoss.pre_vect.y = "<<pickPoss[0].pre_vect.vect_y<<std::endl;
        std::cout<<"pickPoss.pre_vect.z = "<<pickPoss[0].pre_vect.vect_z<<std::endl;
        std::cout<<"pickPoss.vect.x = "<<pickPoss[0].vect.vect_x<<std::endl;
        std::cout<<"pickPoss.vect.y = "<<pickPoss[0].vect.vect_y<<std::endl;
        std::cout<<"pickPoss.vect.z = "<<pickPoss[0].vect.vect_z<<std::endl;
        std::cout<<"pickPoss.euler.p = "<<pickPoss[0].euler.pitch<<std::endl;
        std::cout<<"pickPoss.euler.r = "<<pickPoss[0].euler.roll<<std::endl;
        std::cout<<"pickPoss.euler.y = "<<pickPoss[0].euler.yaw<<std::endl;
        std::cout<<"pickPoss.dist.min = "<<pickPoss[0].dist.dist_min<<std::endl;
        std::cout<<"pickPoss.dist.max = "<<pickPoss[0].dist.dist_max<<std::endl;
    }

    if(_stop_flag)
        return -1;



    pickplace->set_object(objectPose);
    if(this->_pick(pickPoss)  == 0 && ! _stop_flag)
    {
        sleep(2.0);
        if(this->_place(placePoss)  == 0 && !_stop_flag)
        {
            std::cout<<"pick and place succeeful! ! !"<<std::endl;
        }
        else
        {
            std::cerr<<"place failed! ! !"<<std::endl;
            return -1;
        }
    }
    else
    {
        std::cerr<<"pick failed! ! !"<<std::endl;
        return -1;
    }
}

int PickPlace::_gen_pick_place(geometry_msgs::Pose pickPos,geometry_msgs::Pose placePos)
{
    generator->set_pick_pose(pickPos);
    generator->set_place_pose(placePos);
    generator->gen_pick_pose();
    generator->gen_place_pose();
    return 0;
}

int PickPlace::_pick(pose_vec pickPos)
{
     this->pickplace->set_pick_poses(pickPos);
     return this->pickplace->pick();
}

int PickPlace::_place(pose_vec placePos)
{
    this->pickplace->set_place_poses(placePos);
    return this->pickplace->place();
}

int PickPlace::freeback(std::string &status)
{
    std::string state;
    generator->generator_freeback(state);
    pickplace->pickplace_freeback(state);
    status = state;
    return 0;
}

int PickPlace::stop()
{
    _stop_flag = true;
    generator->stop_generator();
    pickplace->stop_pickplace();
    return 0;
}

