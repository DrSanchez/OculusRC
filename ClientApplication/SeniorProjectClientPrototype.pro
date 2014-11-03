TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    steeringwheelcontroller.cpp \
    controllermanager.cpp \
    xinputcontrolstate.cpp

RESOURCES += qml.qrc

# Add C++ 11 support
CONFIG   += c++11 (Qt5)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    steeringwheelcontroller.h \
    XInput.h \
    controllermanager.h \
    xinputcontrolstate.h

win32:LIBS += $${_PRO_FILE_PWD_}/XInput.lib

OTHER_FILES += \
    $${_PRO_FILE_PWD_}/XInput.lib
