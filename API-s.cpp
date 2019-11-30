#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>
#include <QDebug>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include "API.h"

bool Gazua::API::refreshCoinInfos(std::shared_ptr<std::unordered_map<std::string, CoinInfo>> coinInfos) {

    QNetworkAccessManager networkManager;
    QUrl detailUrl("https://api.korbit.co.kr/v1/ticker/detailed/all");
    QUrl constraintUrl("https://api.korbit.co.kr/v1/constants");
    QNetworkRequest request;
    
    request.setUrl(detailUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    connect(&networkManager, SIGNAL(finished(m_refreshCoinInfosReply)), this, SLOT(onResult(m_refreshCoinInfosReply)));
    if (m_currentReply->error() != QNetworkReply::NoError) return false;
    QString detailData = (QString) m_refreshCoinInfosReply->readAll();

    request.setUrl(constraintUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    connect(&networkManager, SIGNAL(finished(m_refreshCoinInfosReply)), this, SLOT(onResult(m_refreshCoinInfosReply)));
    if (m_currentReply->error() != QNetworkReply::NoError) return false;
    QString constraintData = (QString) m_refreshCoinInfosReply->readAll();


    QJsonDocument detailDoc = QJsonDocument::fromJson(detailData.toUtf8());
    QJsonDocument constraintDoc = QJsonDocument::fromJson(constraintData.toUtf8());
	
    QJsonObject detailObj = detailDoc.object();
    QJsonObject constraintObj = constraintDoc.object().value(QString("exchange")).toObject();
	
	
    for(auto coin : CoinType::coin_type) {
    	
        QJsonValue coinDetailVal = detailObj.value(QString(coin));
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
        
        QJsonValue coinConstraintVal = constraintObj.value(QString(coin));
        QJsonObject coinConstraintObj = coinConstraintVal.toObject();

        QJsonValue tick_size = coinDetailObj.value(QString("tick_size"));
        QJsonValue min_price = coinDetailObj.value(QString("min_price"));
        QJsonValue max_price = coinDetailObj.value(QString("max_price"));
        QJsonValue order_min_size = coinDetailObj.value(QString("order_min_size"));
        QJsonValue order_max_size = coinDetailObj.value(QString("order_max_size"));

        CoinInfo coinInfo = new CoinInfo(
		                                    timestamp.toString().toDouble(),
		                                    last.toString().toDouble(),
		                                    open.toString().toDouble(),
		                                    bid.toString().toDouble(),
		                                    ask.toString().toDouble(),
		                                    low.toString().toDouble(),
		                                    high.toString().toDouble(),
		                                    volume.toString().toDouble(),
		                                    change.toString().toDouble(),
		                                    changePercent.toString().toDouble(),
		                                    tick_size.toString().toDouble(),
		                                    min_price.toString().toDouble(),
		                                    max_price.toString().toDouble(),
		                                    order_min_size.toString().toDouble(),
		                                    order_max_size.toString().toDouble()
		                                );
        coinInfos.insert(std::make_pair(coin, CoinInfo));
	    
    }
    
    return true;
}

