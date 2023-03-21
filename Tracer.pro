QT += core gui
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        hitable.cpp \
        main.cpp \
        ray.cpp \
        renderer.cpp \
        sphere.cpp

LIBS += -lsfml-window -lsfml-system -lsfml-graphics

HEADERS += \
    helper.h \
    hitable.h \
    ray.h \
    renderer.h \
    sphere.h
