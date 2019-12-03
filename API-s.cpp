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

    //qDebug() << coinInfos->value("mkr_krw").last;

    //qDebug() << (coinInfos->find("mkr_krw"))->timestamp;

    QJsonObject detailObject;
    QJsonObject constraintObject;

    QNetworkRequest detailRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}};
    QNetworkReply *detailReply = m_qnam.get(detailRequest);
    connect(detailReply, &QNetworkReply::finished, this, [this, detailReply, &detailObject] () {
        detailObject = QJsonDocument::fromJson(detailReply->readAll()).object();
        qDebug() << detailObject.keys();

        detailReply->close();
        // detailReply->deleteLater(); not sure
    });
    QNetworkRequest constraintRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}};
    QNetworkReply *constraintReply = m_qnam.get(constraintRequest);
    connect(constraintReply, &QNetworkReply::finished, this, [this, constraintReply, &constraintObject] () {
        constraintObject = QJsonDocument::fromJson(constraintReply->readAll()).object()["exchange"].toObject();
        constraintReply->close();
        // constraintReply->deleteLater(); not sure
    });

    for(const QString& coinKey : detailObject.keys()) {

        if (coinInfos->contains(coinKey) == false) {
            CoinInfo *newCoinInfo = new CoinInfo();
            coinInfos->insert(coinKey, *newCoinInfo);
        }

        /*
        bool ok;
        coinInfos->find(coinKey).value().timestamp = detailObject.value(coinKey).toObject().value("timestamp").toString().toLongLong(&ok, 10);
        coinInfos->find(coinKey).value().last = detailObject.value(coinKey).toObject().value("last").toDouble();
        coinInfos->find(coinKey).value().open = detailObject.value(coinKey).toObject().value("open").toDouble();
        coinInfos->find(coinKey).value().bid = detailObject.value(coinKey).toObject().value("bid").toDouble();
        coinInfos->find(coinKey).value().ask = detailObject.value(coinKey).toObject().value("ask").toDouble();
        coinInfos->find(coinKey).value().low = detailObject.value(coinKey).toObject().value("low").toDouble();
        coinInfos->find(coinKey).value().high = detailObject.value(coinKey).toObject().value("high").toDouble();
        coinInfos->find(coinKey).value().volume = detailObject.value(coinKey).toObject().value("volume").toDouble();
        coinInfos->find(coinKey).value().change = detailObject.value(coinKey).toObject().value("change").toDouble();
        coinInfos->find(coinKey).value().changePercent = detailObject.value(coinKey).toObject().value("changePercent").toDouble();
        */
    }

    for(const QString& coinKey : constraintObject.keys()) {

        /*
        coinInfos->find(coinKey).value().tick_size = constraintObject.value(coinKey).toObject().value("tick_size").toDouble();
        coinInfos->find(coinKey).value().min_price = constraintObject.value(coinKey).toObject().value("min_price").toDouble();
        coinInfos->find(coinKey).value().max_price = constraintObject.value(coinKey).toObject().value("max_price").toDouble();
        coinInfos->find(coinKey).value().order_min_size = constraintObject.value(coinKey).toObject().value("order_min_size").toDouble();
        coinInfos->find(coinKey).value().order_max_size = constraintObject.value(coinKey).toObject().value("order_max_size").toDouble();
        */
    }
    return true;
}

