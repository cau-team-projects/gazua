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

    QNetworkAccessManager networkManager;
    QUrl detailUrl("https://api.korbit.co.kr/v1/ticker/detailed/all");
    QUrl constraintUrl("https://api.korbit.co.kr/v1/constants");
    QNetworkRequest request;
    
    request.setUrl(detailUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    connect(&networkManager, SIGNAL(finished(m_refreshCoinInfosReply)), this, SLOT(onResult(m_refreshCoinInfosReply)));
    if (m_refreshCoinInfosReply->error() != QNetworkReply::NoError) return false;
    QString detailData = (QString) m_refreshCoinInfosReply->readAll();

    request.setUrl(constraintUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    connect(&networkManager, SIGNAL(finished(m_refreshCoinInfosReply)), this, SLOT(onResult(m_refreshCoinInfosReply)));
    if (m_refreshCoinInfosReply->error() != QNetworkReply::NoError) return false;
    QString constraintData = (QString) m_refreshCoinInfosReply->readAll();


    QJsonDocument detailDoc = QJsonDocument::fromJson(detailData.toUtf8());
    QJsonDocument constraintDoc = QJsonDocument::fromJson(constraintData.toUtf8());
	
    QJsonObject detailObj = detailDoc.object();
    QJsonObject constraintObj = constraintDoc.object().value(QString("exchange")).toObject();
	
	
    for(QString coin : Gazua::CoinType::coinType) {
    	
        QJsonValue coinDetailVal = detailObj.value(coin);
        QJsonObject coinDetailObj = coinDetailVal.toObject();

        QJsonValue timestamp = coinDetailObj.value(QString("timestamp"));
        QJsonValue last = coinDetailObj.value(QString("last"));
        QJsonValue open = coinDetailObj.value(QString("open"));
        QJsonValue bid = coinDetailObj.value(QString("bid"));
        QJsonValue ask = coinDetailObj.value(QString("ask"));
        QJsonValue low = coinDetailObj.value(QString("low"));
        QJsonValue high = coinDetailObj.value(QString("high"));
        QJsonValue volume = coinDetailObj.value(QString("volume"));
        QJsonValue change = coinDetailObj.value(QString("change"));
        QJsonValue changePercent = coinDetailObj.value(QString("changePercent"));
        
        QJsonValue coinConstraintVal = constraintObj.value(coin);
        QJsonObject coinConstraintObj = coinConstraintVal.toObject();

        QJsonValue tick_size = coinDetailObj.value(QString("tick_size"));
        QJsonValue min_price = coinDetailObj.value(QString("min_price"));
        QJsonValue max_price = coinDetailObj.value(QString("max_price"));
        QJsonValue order_min_size = coinDetailObj.value(QString("order_min_size"));
        QJsonValue order_max_size = coinDetailObj.value(QString("order_max_size"));

        (coinInfos.get())->find(coin).value().timestamp = timestamp.toString().toDouble();
        (coinInfos.get())->find(coin).value().last = last.toString().toDouble();
        (coinInfos.get())->find(coin).value().open = open.toString().toDouble();
        (coinInfos.get())->find(coin).value().bid = bid.toString().toDouble();
        (coinInfos.get())->find(coin).value().ask = ask.toString().toDouble();
        (coinInfos.get())->find(coin).value().low = low.toString().toDouble();
        (coinInfos.get())->find(coin).value().high = high.toString().toDouble();
        (coinInfos.get())->find(coin).value().volume = volume.toString().toDouble();
        (coinInfos.get())->find(coin).value().change = change.toString().toDouble();
        (coinInfos.get())->find(coin).value().changePercent = changePercent.toString().toDouble();
        (coinInfos.get())->find(coin).value().tick_size = tick_size.toString().toDouble();
        (coinInfos.get())->find(coin).value().min_price = min_price.toString().toDouble();
        (coinInfos.get())->find(coin).value().max_price = max_price.toString().toDouble();
        (coinInfos.get())->find(coin).value().order_min_size = order_min_size.toString().toDouble();
        (coinInfos.get())->find(coin).value().order_max_size = order_max_size.toString().toDouble();

    }
    
    return true;
}

