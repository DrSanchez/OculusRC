#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include "qtquick2applicationviewer.h"
#include "networkmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;

    NetworkManager * net = new NetworkManager();
    viewer.rootContext()->setContextProperty("NetworkManager", net);
    viewer.setMainQmlFile(QStringLiteral("qml/ServerApplication/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
