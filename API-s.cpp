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

        qDebug() << "------------------------------test2222222-----------------------------";
        for(const QString& coinName : detailObject.keys()) {

            QVariantMap coinFields;
            if (!coinInfo.contains(coinName)) coinFields.insert(coinName, QVariant());
            else coinFields = qvariant_cast<QVariantMap>(coinInfo[coinName]);

            for(const QString& fieldName : detailObject[coinName].toObject().keys()) {
                qDebug() << "------------------------------test3333333-----------------------------";

                if (!coinFields.contains(fieldName)) coinFields.insert(fieldName, detailObject.value(coinName).toObject().value(fieldName).toVariant());
                else coinFields[fieldName] = detailObject.value(coinName).toObject().value(fieldName).toVariant();
            }
qDebug() << "------------------------------test444444444-----------------------------";

        }
qDebug() << "------------------------------test666666-----------------------------";
        detailReply->close();
        qDebug() << "------------------------------test7777777-----------------------------";
        // detailReply->deleteLater(); not sure
    });

    /*
    QNetworkRequest constraintRequest{QUrl{"https://api.korbit.co.kr/v1/constants"}};
    QNetworkReply *constraintReply = m_qnam.get(constraintRequest);
    connect(constraintReply, &QNetworkReply::finished, this, [this, constraintReply, coinInfo] () {
        QJsonObject constraintObject = QJsonDocument::fromJson(constraintReply->readAll()).object()["exchange"].toObject();

        for(const QString& coinKey : constraintObject.keys()) {
            QVariantMap refreshedCoinInfo = coinInfo->getCoinFields(coinKey);
            for(const QString& fieldKey : constraintObject[coinKey].toObject().keys()) {
                refreshedCoinInfo[fieldKey] = constraintObject.value(coinKey).toObject().value(fieldKey).toVariant();
                //qDebug() << refreshedCoinInfo[fieldKey];
            }
            coinInfo->remove(coinKey);
            coinInfo->append(coinKey, refreshedCoinInfo);
        }
        constraintReply->close();
        // constraintReply->deleteLater(); not sure
    });
*/

    //qDebug() << "------------------------------test-----------------------------";
    //qDebug() << qvariant_cast<QVariantMap>(coinInfo->getCoinInfo().value("btc_krw")).keys();
    //qDebug() << "------------------------------testend--------------------------";

    return true;
}

