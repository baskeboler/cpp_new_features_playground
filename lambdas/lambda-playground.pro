TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    addressbookentry.cpp \
    addressbook.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    addressbookentry.h \
    addressbook.h

