#include <QtGui/QScreen>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "steeringwheelcontroller.h"
#include "clientnetworkmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QScreen * screen = app.primaryScreen();
    bool showFullscreen = false;
    int screenWidth = 0;
    int screenHeight = 0;

    if (showFullscreen)
    {
        screenWidth = screen->size().width();
        screenHeight = screen->size().height();
    }
    else if (!showFullscreen)
    {
        screenWidth = screen->availableGeometry().width();
        screenHeight = screen->availableGeometry().height();
    }

    SteeringWheelController * wheelController = new SteeringWheelController(0);
    ClientNetworkManager * clientNetwork = new ClientNetworkManager(wheelController);
    wheelController->startPolling(20);
    engine.rootContext()->setContextProperty("ClientNetwork", clientNetwork);
    engine.rootContext()->setContextProperty("SteeringWheel", wheelController);
    engine.rootContext()->setContextProperty("ScreenWidth", screenWidth);
    engine.rootContext()->setContextProperty("ScreenHeight", screenHeight);
    engine.rootContext()->setContextProperty("ShowFullscreen", showFullscreen);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
