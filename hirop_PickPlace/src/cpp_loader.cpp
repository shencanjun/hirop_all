#include "cpp_loader.h"

using namespace hirop_pickPlace;

CppLoader::CppLoader(){
    //this->loader = HPluginLoader::getLoader();
}

IGenerator* CppLoader::loadGenerator(std::string generatorName,std::string path){

    HPlugin *plugin;
    HPluginLoader *loaderg;
    loaderg = HPluginLoader::getLoader();
    loaderg->setPath(path);
    plugin = loaderg->load(generatorName);
    if(plugin == NULL)
        return NULL;
    return plugin->instance<IGenerator>();
}

IPickPlace* CppLoader::loadPickPlace(std::string PickPlaceName,std::string path){
    HPlugin *plugin;
    HPluginLoader *loaderp;
    loaderp = HPluginLoader::getLoader();
    loaderp->setPath(path);
    plugin = loaderp->load(PickPlaceName);
    if(plugin == NULL)
        return NULL;

    return plugin->instance<IPickPlace>();
}


