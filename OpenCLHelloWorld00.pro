TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++14

LIBS += /usr/lib/x86_64-linux-gnu/libOpenCL.so


SOURCES += main.cpp

DISTFILES += \
    hello_world.cl
