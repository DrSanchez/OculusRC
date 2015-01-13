TEMPLATE = app

QT += qml quick

SOURCES += Source/main.cpp \
    Source/steeringwheelcontroller.cpp \
    Source/controllermanager.cpp \
    Source/xinputcontrolstate.cpp \
    Source/clientnetworkmanager.cpp

RESOURCES += $${_PRO_FILE_PWD_}/QML/qml.qrc \
    $${_PRO_FILE_PWD_}/ApplicationImages/ApplicationImages.qrc \
    $${_PRO_FILE_PWD_}/BackgroundImages/BackgroundImages.qrc \
    $${_PRO_FILE_PWD_}/TextImages/TextImages.qrc

# Add C++ 11 support
CONFIG   += c++11 (Qt5)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Include/steeringwheelcontroller.h \
    Include/XInput.h \
    Include/controllermanager.h \
    Include/xinputcontrolstate.h \
    Include/clientnetworkmanager.h

# Todo: Add oculus sdk libraries and headers

win32:INCLUDEPATH += $${_PRO_FILE_PWD_}/Include
win32:LIBS += $${_PRO_FILE_PWD_}/Libraries/XInput.lib

OTHER_FILES += \
    $${_PRO_FILE_PWD_}/XInput.lib
