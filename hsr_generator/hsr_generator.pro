TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
TARGET = hsr_generator

DEFINES += __LINUX__

SOURCES +=  \
    src/generator.cpp

HEADERS += \
    include/generator.h \
    ../hirop_PickPlace/3rd/include/hlibload.h \
    ../hirop_PickPlace/3rd/include/hplugin_define.h \
    ../hirop_PickPlace/3rd/include/hplugin.h \
    ../hirop_PickPlace/3rd/include/hpluginloader.h \
    ../hirop_PickPlace/include/igenerator.h \
    ../hirop_PickPlace/include/pickandplac.h \
    ../hirop_PickPlace/include/c_base_generator.h
    /opt/ros/indigo/include

INCLUDEPATH += /opt/ros/indigo/include/ \
               ../hirop_PickPlace/include/ \
               ../hirop_PickPlace/


LIBS += -Wl,-rpath=/home/shen/catkin_ws/src/hirop_pickandplace/hirop_PickPlace/3rd/libs  -L/home/shen/catkin_ws/src/hirop_pickandplace/hirop_PickPlace/3rd/libs -ldl -lHPlugin
