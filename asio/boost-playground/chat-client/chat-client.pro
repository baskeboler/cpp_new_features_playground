TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
LIBS += -lboost_system -lboost_thread -lpthread

SOURCES += main.cpp \
    ../chatmessage.cpp \
    chatclient.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../chatmessage.h \
    chatclient.h

