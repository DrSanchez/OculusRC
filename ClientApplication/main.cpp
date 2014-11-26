#include <QtGui/QScreen>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "controllermanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QScreen * screen = app.primaryScreen();
    bool showFullscreen = true;
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

    ControllerManager * controllerManager = new ControllerManager();

    engine.rootContext()->setContextProperty("ControllerManager", controllerManager);
    engine.rootContext()->setContextProperty("ScreenWidth", screenWidth);
    engine.rootContext()->setContextProperty("ScreenHeight", screenHeight);
    engine.rootContext()->setContextProperty("ShowFullscreen", showFullscreen);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
