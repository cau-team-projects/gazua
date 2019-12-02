#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QMap>
#include <QNetworkRequest>
#include <QDebug>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include "API.h"

bool Gazua::API::refreshCoinInfos(std::shared_ptr<QMap<QString, CoinInfo>> coinInfos) {

    QUrl detailUrl("https://api.korbit.co.kr/v1/ticker/detailed/all");
    QUrl constraintUrl("https://api.korbit.co.kr/v1/constants");
    QByteArray detailJson;
    QByteArray constraintJson;

    auto detailReply = m_qnam.get(QNetworkRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}});
    connect(detailReply, &QNetworkReply::finished, this, [detailReply, &detailJson] () {
        detailJson = detailReply->readAll();
        detailReply->close();
        // detailReply->deleteLater(); not sure
    });
    auto constraintReply = m_qnam.get(QNetworkRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}});
    connect(constraintReply, &QNetworkReply::finished, this, [constraintReply, &constraintJson] () {
        constraintJson = constraintReply->readAll();
        constraintReply->close();
        // constraintReply->deleteLater(); not sure
    });

    QJsonObject detailObject = QJsonDocument::fromJson(detailJson).object();
    QJsonObject constraintObject = QJsonDocument::fromJson(constraintJson).object().value("exchange").toObject();

    foreach (const QString& coinKey, detailObject.keys()) {
    	
        if (coinInfos->contains(coinKey) == false) {
            CoinInfo newCoinInfo;
            coinInfos->insert(coinKey, newCoinInfo);
        }

        bool ok;
        coinInfos->find(coinKey).value().timestamp = detailObject.value("timestamp").toString().toLong(&ok, 10);
        coinInfos->find(coinKey).value().last = detailObject.value("last").toDouble();
        coinInfos->find(coinKey).value().open = detailObject.value("open").toDouble();
        coinInfos->find(coinKey).value().bid = detailObject.value("bid").toDouble();
        coinInfos->find(coinKey).value().ask = detailObject.value("ask").toDouble();
        coinInfos->find(coinKey).value().low = detailObject.value("low").toDouble();
        coinInfos->find(coinKey).value().high = detailObject.value("high").toDouble();
        coinInfos->find(coinKey).value().volume = detailObject.value("volume").toDouble();
        coinInfos->find(coinKey).value().change = detailObject.value("change").toDouble();
        coinInfos->find(coinKey).value().changePercent = detailObject.value("changePercent").toDouble();

    }

    foreach (const QString& coinKey, constraintObject.keys()) {
        QJsonObject coinObject = QJsonDocument::fromJson(coinKey.toUtf8()).object();
        coinInfos->find(coinKey).value().tick_size = constraintObject.value("tick_size").toDouble();
        coinInfos->find(coinKey).value().min_price = constraintObject.value("min_price").toDouble();
        coinInfos->find(coinKey).value().max_price = constraintObject.value("max_price").toDouble();
        coinInfos->find(coinKey).value().order_min_size = constraintObject.value("order_min_size").toDouble();
        coinInfos->find(coinKey).value().order_max_size = constraintObject.value("order_max_size").toDouble();
    }
    
    return true;
}

