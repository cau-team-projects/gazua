
#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "API.h"
#include "CoinModel.h"
#include "UserInfo.h"

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

    QQuickView viewer;
    Gazua::API api{std::move(key), std::move(secret)};
    api.access();
    auto userInfo = std::make_shared<Gazua::UserInfo>();
    api.refreshUserInfo(userInfo);

    //viewer.rootContext()->setContextProperty("api",&api);
    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.setTitle(QStringLiteral("GAZUA"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setColor(QColor("#FCFCFC"));
    viewer.show();

    return app.exec();
}
