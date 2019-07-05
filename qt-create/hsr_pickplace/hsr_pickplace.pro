TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../hsr_pickplace/src/pickPlace.cpp

HEADERS += \
    ../../hsr_pickplace/include/pickPlace.h

INCLUDEPATH += \
    ../../hsr_pickplace/include \
    ../../hirop_PickPlace/include \
    ../../../../devel/include \
    /opt/ros/kinetic/include
