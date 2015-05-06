# Add more folders to ship with the application, here
folder_01.source = qml/ServerApplication
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    networkmanager.cpp \
    cameracontroller.cpp \
    packetmanager.cpp \
    pwmcontroller.cpp \
    motorcontroller.cpp \
    rcmanager.cpp \
    servocontroller.cpp \
    boostcontroller.cpp

QMAKE_CXXFLAGS += -std=c++11

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    networkmanager.h \
    cameracontroller.h \
    packetmanager.h \
    pwmcontroller.h \
    motorcontroller.h \
    rcmanager.h \
    servocontroller.h \
    boostcontroller.h \
    safequeue.h
