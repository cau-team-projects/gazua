#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTreeView>
#include <QApplication>
#include "API.h"
#include "CoinInfoModel.h"
#include "CoinTreeModel.h"
#include "CoinTreeItem.h"
#include "UserInfo.h"

int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    QFile apiKeyFile("apikey.txt");
    if(!apiKeyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "API KEY NOT FOUND!";
        return 1;
    }

    QString key;
    QString secret;

    QTextStream apiKeyStream(&apiKeyFile);

    if(!apiKeyStream.atEnd())
        key = std::move(apiKeyStream.readLine());
    if(!apiKeyStream.atEnd())
        secret = std::move(apiKeyStream.readLine());

    Gazua::API api{std::move(key), std::move(secret)};
    api.access();
    auto userInfo = std::make_shared<Gazua::UserInfo>();
    api.refreshUserInfo(userInfo);

    QStringList coinInfoModelHeader;
    coinInfoModelHeader << "1" << "2" << "3";

    auto coinTreeModel = std::make_shared<Gazua::CoinTreeModel>(coinInfoModelHeader, QString(), nullptr);
    api.refreshCoinInfo(coinTreeModel);

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    //context->setContextProperty("userInfo", userInfo.get());
    context->setContextProperty("coinTreeModel", coinTreeModel.get());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QTreeView view;
    //view.setModel(userInfo.get());
    view.setModel(coinTreeModel.get());
    view.setWindowTitle(QObject::tr("hello"));
    view.show();


    return app.exec();
}
