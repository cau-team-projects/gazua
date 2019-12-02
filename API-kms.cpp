#include "API.h"
#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QUrl>
#include <QJsonDocument>

bool Gazua::API::getOrders(std::shared_ptr<QMap<uint64_t, Order>> orders, const QString& coinName, const QVector<uint64_t>& ids, uint64_t limit){

    QUrlQuery qUrl;
    QString tmp("");
    qUrl.addQueryItem("currency_pair", coinName);
    for(auto i = ids.begin(); i != ids.end(); i++)
        tmp.append(QString("id=%1&").arg(QString::number(*i)));
    tmp.chop(1);
    qUrl.addQueryItem("id", tmp);
    qUrl.addQueryItem("limit", QString::number(limit));

    QNetworkRequest network;
    auto header = QString("Bearer %1").arg(*(this->m_token->accessToken()));
    network.setRawHeader(QByteArray("Authorization"), header.toUtf8());

    network.setUrl(qUrl.toString());


    auto reply = m_qnam.get(network);
    connect(reply, &QNetworkReply::finished, this, [reply, orders]() {
        auto jsonArr =  QJsonDocument::fromJson(reply->readAll()).array();

        for(auto iter = jsonArr.begin(); iter != jsonArr.end(); iter++) {
            Order order((*iter).toObject()["currency_pair"].toString(), (*iter).toObject()["side"].toString()
                    ,(*iter).toObject()["avg_price"].toInt(),(*iter).toObject()["price"].toInt()
                    ,(*iter).toObject()["order_amount"].toDouble(),(*iter).toObject()["filled_amount"].toDouble()
                    ,(*iter).toObject()["order_total"].toInt(), (*iter).toObject()["filled_total"].toInt()
                    ,(*iter).toObject()["created_at"].toInt(), (*iter).toObject()["last_filled_at"].toInt()
                    ,(*iter).toObject()["status"].toString(), (*iter).toObject()["fee"].toDouble());

            orders->insert((*iter).toObject()["id"].toInt(), order);
        }
        reply->close();
    });

    return true;
}
