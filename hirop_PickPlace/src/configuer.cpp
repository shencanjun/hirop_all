#include "configuer.h"

using namespace hirop_pickPlace;

Configure::Configure(std::string fileName)
{
    try{
        config = YAML::LoadFile(fileName);
    }catch(std::exception e){
        std::cerr << "Load configure file error" << std::endl;
    }
}

int Configure::getObjectName(std::string &objName){
    if(!config["objectName"]){
        std::cerr << "Get Object name error:  No objectName node" << std::endl;
        return -1;
    }
    objName = config["objectName"].as<std::string>();
    configDebug("Get objectName: %s", objName.c_str());

    return 0;
}

int Configure::getGeneratorName(std::string &generatorName){

    if(!config["generatorName"]){
        std::cerr << "Get generator name error:  No generatorName node" << std::endl;
        return -1;
    }
    generatorName = config["generatorName"].as<std::string>();
    configDebug("Get generatorName: %s", generatorName.c_str());

    return 0;
}

int Configure::getPickPlacerName(std::string &pickpalcerName)
{
    if(!config["PickPlacerName"]){
        std::cerr << "Get PickPlacer name error:  No PickPlacerName node" << std::endl;
        return -1;
    }
    pickpalcerName = config["PickPlacerName"].as<std::string>();
    configDebug("Get PickPlacerName: %s", pickpalcerName.c_str());

    return 0;
}

int Configure::getGeneratorPath(std::string &generatorPath)
{
    if(!config["GeneratorPath"])
    {
        std::cerr << "Get GeneratorPath error:  No Generator path node" << std::endl;
        return -1;
    }
    generatorPath = config["GeneratorPath"].as<std::string>();
    return 0;
}

int Configure::getPickPlacerPath(std::string &pickpalcerPath)
{
    if(!config["PickpalcerPath"])
    {
        std::cerr << "Get PickpalcerPath error:  No Pickpalcer path node" << std::endl;
        return -1;
    }
    pickpalcerPath = config["PickpalcerPath"].as<std::string>();

    return 0;
}



