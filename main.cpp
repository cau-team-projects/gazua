
#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "API.h"
#include "CoinModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //QQmlApplicationEngine engine;

    //CoinModel *coinModel = new CoinModel(nullptr);

    //QMap<QString, Gazua::CoinInfo> *tempCoinInfo = new QMap<QString, Gazua::CoinInfo>();
    //std::shared_ptr<QMap<QString, Gazua::CoinInfo>> tempCoinInfoPtr(tempCoinInfo);
    //api.refreshCoinInfos(tempCoinInfoPtr);
    //coinModel->append(tempCoinInfoPtr);

    //engine.rootContext()->setContextProperty("coinModel", coinModel);

    QQuickView viewer;
    Gazua::API api;
    api.access("key", "secret");
    //viewer.rootContext()->setContextProperty("api",&api);
    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.setTitle(QStringLiteral("GAZUA"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setColor(QColor("#FCFCFC"));
    viewer.show();

    return app.exec();
}
