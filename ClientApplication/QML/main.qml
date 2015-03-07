import QtQuick 2.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

FocusScope
{
    id: applicationFocus
    property alias color: clientMain.color
    x: clientMain.x; y: clientMain.y
    width: clientMain.width; height: clientMain.height

    property bool oculusConnectionStatus: false
    property bool controllerConnectionStatus: SteeringWheel.connected
    property bool serverConnectionStatus: ClientNetwork.connected

    Component.onCompleted:
    {//app init code
        splashSequence.focus = true;
        splashSequence.running = true;//start the splash sequence
    }

    Window
    {
        id: clientMain
        visible: true
        minimumHeight: 480
        minimumWidth: minimumHeight * 1.4
        width: ScreenWidth * 0.88
        height: ScreenHeight * 0.88
        visibility:
        {
            if (ShowFullscreen)
                clientMain.visibility = "FullScreen";
            else if (!ShowFullscreen)
                clientMain.visibility = "Windowed";
        }

        property string customState: "INITIALIZING"

        onCustomStateChanged:
        {
            if (customState == "INITIALIZING")
            {
                //current do nothing
            }
            else if (customState == "HOME")
            {
                //driveMenu.visible = false;
                //calibrateMenu.visible = false;
                //testMenu.visible = false;
                //settingsMenu.visible = false;
                if (driveMenu.x != homeScreen.width)
                    driveMenu.x = homeScreen.width
                if (settingsMenu.x != homeScreen.width)
                    settingsMenu.x = homeScreen.width;
                homeScreen.x = 0;
                homeScreen.setDefaultFocus();
            }
            else if (customState == "DRIVE")
            {
                //ClientNetwork.setMessage("camStart");
                driveMenu.visible = true;
                //calibrateMenu.visible = false;
                //testMenu.visible = false;
                //settingsMenu.visible = false;
                homeScreen.x = 0 - homeScreen.width;
                driveMenu.x = 0;
                driveMenu.setDefaultFocus();
            }
            else if (customState == "CALIBRATE")
            {
                //driveMenu.visible = false;
                //calibrateMenu.visible = true;
                //testMenu.visible = false;
                //settingsMenu.visible = false;
                //homeScreen.x = 0 - homeScreen.width;
                //calibrateMenu.x = 0;
                //calibrateMenu.setDefaultFocus();
            }
            else if (customState == "TEST")
            {
                //driveMenu.visible = false;
                //calibrateMenu.visible = false;
                //testMenu.visible = true;
                //settingsMenu.visible = false;
                //homeScreen.x = 0 - homeScreen.width;
                //testMenu.x = 0;
                //testMenu.setDefaultFocus();
            }
            else if (customState == "SETTINGS")
            {
                //driveMenu.visible = false;
                //calibrateMenu.visible = false;
                //testMenu.visible = false;
                settingsMenu.visible = true;
                homeScreen.x = 0 - homeScreen.width;
                settingsMenu.x = 0;
                settingsMenu.setDefaultFocus();
            }
            else if (customState == "ALERT")
            {

            }
        }

        //instantiate and name the app theme object
        ColorTheme{id:clientTheme}
        SplashSequenceController
        {
            id: splashSequence
            onRunningChanged:
            {
                if(!running)
                {
                    homeScreen.setDefaultFocus();
                    clientMain.customState = "HOME";
                    splashSequence.destroy();
                }
            }
        }
        MessageAlertBox{id:alertBox}
        Home{id:homeScreen}
        SettingsMenu{id:settingsMenu}
        DriveMenu{id:driveMenu}
    }
}
