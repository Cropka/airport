QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    bus.cpp \
    car.cpp \
    mainwindow.cpp \
    passangerplane.cpp \
    plane.cpp \
    postalplane.cpp \
    rampstairs.cpp \
    resource.cpp \
    controller.cpp \
    event.cpp \
    runway.cpp \
    simulator.cpp \
    gateway.cpp \
    agent.cpp \
    airport.cpp

HEADERS += \
    bus.h \
    car.h \
    mainwindow.h \
    passangerplane.h \
    plane.h \
    postalplane.h \
    rampstairs.h \
    resource.h \
    controller.h \
    event.h \
    runway.h \
    simulator.h \
    gateway.h \
    agent.h \
    airport.h

QT += widgets
