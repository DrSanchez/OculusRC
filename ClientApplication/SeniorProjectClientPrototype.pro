TEMPLATE = app

QT += qml quick opengl multimedia

SOURCES += Source/main.cpp \
    Source/steeringwheelcontroller.cpp \
    Source/controllermanager.cpp \
    Source/xinputcontrolstate.cpp \
    Source/clientnetworkmanager.cpp \
    Source/packetmanager.cpp \
    Source/oculusmanager.cpp

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
include(QmlVlc/QmlVlc.pri)

HEADERS += \
    Include/steeringwheelcontroller.h \
    Include/XInput.h \
    Include/controllermanager.h \
    Include/xinputcontrolstate.h \
    Include/clientnetworkmanager.h \
    Include/packetmanager.h \
    Include/oculusmanager.h

win32:INCLUDEPATH += $${_PRO_FILE_PWD_}/Include \
		     $${_PRO_FILE_PWD_}/libvlc-sdk/include/ \
		     C:/Users/Jack/Documents/libovr/LibOVR/Include/

win32:LIBS += $${_PRO_FILE_PWD_}/Libraries/XInput.lib \
	      $${_PRO_FILE_PWD_}/libvlc-sdk/lib/libvlc.lib \
	      $${_PRO_FILE_PWD_}/libvlc-sdk/lib/libvlccore.lib \
	      C:/Users/Jack/Documents/libovr/build_libovr/LibOVR/libovr.a -Libovr -lgdi32 -lwinmm -lsetupapi -lole32 -loleaut32 -lws2_32 -ldbghelp -lkernel32 -luser32
