QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ./factory \
    ./agents \
    ./resources
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    agents/agent.cpp \
    agents/bus.cpp \
    agents/car.cpp \
    agents/passangerplane.cpp \
    agents/plane.cpp \
    agents/postalplane.cpp \
    agents/rampstairs.cpp \
    animationtimer.cpp \
    factory/agentfactory.cpp \
    factory/busfactory.cpp \
    factory/gatewayfactory.cpp \
    factory/landingrunwayfactory.cpp \
    factory/landingspotfactory.cpp \
    factory/passengerplanefactory.cpp \
    factory/postalplanefactory.cpp \
    factory/rampstairsfactory.cpp \
    factory/resourcefactory.cpp \
    factory/takeoffrunwayfactory.cpp \
    mainwindow.cpp \
    controller.cpp \
    event.cpp \
    resources/gateway.cpp \
    resources/landingrunway.cpp \
    resources/landingspot.cpp \
    resources/resource.cpp \
    resources/takeoffrunway.cpp \
    simulator.cpp \
    airport.cpp \
    configparser.cpp

HEADERS += \
    agents/agent.h \
    agents/bus.h \
    agents/car.h \
    agents/passangerplane.h \
    agents/plane.h \
    agents/postalplane.h \
    agents/rampstairs.h \
    animationtimer.h \
    factory/agentfactory.h \
    factory/busfactory.h \
    factory/gatewayfactory.h \
    factory/landingrunwayfactory.h \
    factory/landingspotfactory.h \
    factory/passengerplanefactory.h \
    factory/postalplanefactory.h \
    factory/rampstairsfactory.h \
    factory/resourcefactory.h \
    factory/takeoffrunwayfactory.h \
    mainwindow.h \
    controller.h \
    event.h \
    resources/gateway.h \
    resources/landingrunway.h \
    resources/landingspot.h \
    resources/resource.h \
    resources/takeoffrunway.h \
    simulator.h \
    airport.h \
    configparser.h

QT += widgets

RESOURCES += \
    images.qrc
