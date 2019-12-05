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

bool Gazua::API::refreshCoinInfos(std::shared_ptr<QVariantMap> coinInfos) {

    QJsonObject detailObject;
    QJsonObject constraintObject;

    QNetworkRequest detailRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}};
    QNetworkReply *detailReply = m_qnam.get(detailRequest);
    connect(detailReply, &QNetworkReply::finished, this, [this, detailReply, coinInfos] () {
        QJsonObject detailObject = QJsonDocument::fromJson(detailReply->readAll()).object();

        for(const QString& coinKey : detailObject.keys()) {
            QVariantMap refreshedCoinInfo;

            for(const QString& fieldKey : detailObject[coinKey].toObject().keys()) {
                refreshedCoinInfo[fieldKey] = detailObject.value(coinKey).toObject().value(fieldKey).toVariant();
                //qDebug() << refreshedCoinInfo[fieldKey];
            }
            coinInfos->remove(coinKey);
            coinInfos->insert(coinKey, refreshedCoinInfo);
        }
        qDebug() << "------------------------------apitest--------------------------";
        qDebug() << qvariant_cast<QVariantMap>(coinInfos->value("btc_krw")).keys();
        qDebug() << "------------------------------testend--------------------------";

        detailReply->close();
        // detailReply->deleteLater(); not sure
    });

    QNetworkRequest constraintRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}};
    QNetworkReply *constraintReply = m_qnam.get(constraintRequest);
    connect(constraintReply, &QNetworkReply::finished, this, [this, constraintReply, coinInfos] () {
        QJsonObject constraintObject = QJsonDocument::fromJson(constraintReply->readAll()).object()["exchange"].toObject();

        for(const QString& coinKey : constraintObject.keys()) {
            QVariantMap refreshedCoinInfo;
            if (coinInfos->contains(coinKey) == true) refreshedCoinInfo = qvariant_cast<QVariantMap>(coinInfos->value(coinKey));
            for(const QString& fieldKey : constraintObject[coinKey].toObject().keys()) {
                if (qvariant_cast<QVariantMap>(coinInfos->value(coinKey)).contains(fieldKey) == true) refreshedCoinInfo.insert(fieldKey, constraintObject.value(coinKey).toObject().value(fieldKey).toVariant());
                else refreshedCoinInfo[fieldKey] = constraintObject.value(coinKey).toObject().value(fieldKey).toVariant();
            }
            coinInfos->remove(coinKey);
            coinInfos->insert(coinKey, refreshedCoinInfo);
        }
        constraintReply->close();
        // constraintReply->deleteLater(); not sure
    });

    //qDebug() << "------------------------------test-----------------------------";
    //qDebug() << qvariant_cast<QVariantMap>(coinInfos->value("btc_krw")).keys();
    //qDebug() << "------------------------------testend--------------------------";

    return true;
}

