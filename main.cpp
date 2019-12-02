
#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include "API.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView viewer;
    Gazua::API api;
    //viewer.rootContext()->setContextProperty("api",&api);
    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.setTitle(QStringLiteral("GAZUA"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setColor(QColor("#FCFCFC"));
    viewer.show();

    return app.exec();
}
