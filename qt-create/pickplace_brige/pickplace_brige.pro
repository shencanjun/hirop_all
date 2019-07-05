TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../pick_place_bridge/src/ros_pick_place.cpp \
    ../../pick_place_bridge/src/main.cpp

HEADERS += \
    ../../pick_place_bridge/include/ros_pick_place.h

INCLUDEPATH += \
    ../../pick_place_bridge/include \
    ../../hirop_PickPlace/include \
    ../../../../devel/include \
    /opt/ros/kinetic/include

