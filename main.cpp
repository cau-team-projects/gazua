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

    auto coinInfoModel = std::make_shared<Gazua::CoinInfoModel>();
    api.refreshCoinInfo(coinInfoModel);

    //qDebug() << "------------------------------maintest-------------------------";
    //qDebug() << qvariant_cast<QVariantMap>(coinInfo->getCoinInfo().value("btc_krw")).keys();
    //qDebug() << "------------------------------testend--------------------------";

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    context->setContextProperty("userInfo", userInfo.get());
    //context->setContextProperty("coinInfos", coinInfo.get());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QTreeView view;
    //view.setModel(userInfo.get());
    view.setModel(coinInfoModel.get());
    view.setWindowTitle(QObject::tr("hello"));
    view.show();


    return app.exec();
}
