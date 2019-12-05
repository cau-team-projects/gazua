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
#include <QString>
#include "API.h"

bool Gazua::API::refreshCoinInfo(std::shared_ptr<CoinInfoModel> coinInfoModel) {

    QJsonObject detailObject;
    QJsonObject constraintObject;

    QNetworkRequest detailRequest{QUrl{"https://api.korbit.co.kr/v1/ticker/detailed/all"}};
    QNetworkReply *detailReply = m_qnam.get(detailRequest);
    connect(detailReply, &QNetworkReply::finished, this, [this, detailReply, coinInfoModel] () {
        QJsonObject detailObject = QJsonDocument::fromJson(detailReply->readAll()).object();

        QVariantMap coinInfo = coinInfoModel->getCoinInfo();

        for(const QString& coinName : detailObject.keys()) {

            QVariantMap coinFields;
            if (!coinInfo.contains(coinName)) coinFields.insert(coinName, QVariant());
            else coinFields = qvariant_cast<QVariantMap>(coinInfo[coinName]);

            for(const QString& fieldName : detailObject[coinName].toObject().keys()) {

                if (!coinFields.contains(fieldName)) coinFields.insert(fieldName, detailObject.value(coinName).toObject().value(fieldName).toVariant());
                else coinFields[fieldName] = detailObject.value(coinName).toObject().value(fieldName).toVariant();
            }

        }
        detailReply->close();
        // detailReply->deleteLater(); not sure
    });

    QNetworkRequest constraintRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}};
    QNetworkReply *constraintReply = m_qnam.get(constraintRequest);
    connect(constraintReply, &QNetworkReply::finished, this, [this, constraintReply, coinInfoModel] () {
        QJsonObject constraintObject = QJsonDocument::fromJson(constraintReply->readAll()).object()["exchange"].toObject();

        QVariantMap coinInfo = coinInfoModel->getCoinInfo();

        for(const QString& coinName : constraintObject.keys()) {

            QVariantMap coinFields;
            if (!coinInfo.contains(coinName)) coinFields.insert(coinName, QVariant());
            else coinFields = qvariant_cast<QVariantMap>(coinInfo[coinName]);

            for(const QString& fieldName : constraintObject[coinName].toObject().keys()) {

                if (!coinFields.contains(fieldName)) coinFields.insert(fieldName, constraintObject.value(coinName).toObject().value(fieldName).toVariant());
                else coinFields[fieldName] = constraintObject.value(coinName).toObject().value(fieldName).toVariant();
            }

        }
        constraintReply->close();
        // constraintReply->deleteLater(); not sure
    });

    //qDebug() << "------------------------------test-----------------------------";
    //qDebug() << qvariant_cast<QVariantMap>(coinInfo->getCoinInfo().value("btc_krw")).keys();
    //qDebug() << "------------------------------testend--------------------------";

    return true;
}

