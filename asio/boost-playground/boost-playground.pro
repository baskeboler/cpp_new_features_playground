TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
LIBS += -lboost_system

SOURCES += main.cpp \
    chatmessage.cpp \
    chatparticipant.cpp \
    chatroom.cpp \
    chatsession.cpp \
    chatserver.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    chatmessage.h \
    chatparticipant.h \
    chatroom.h \
    chatsession.h \
    chatserver.h

