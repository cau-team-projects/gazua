#include "API.h"
#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QUrl>
#include <QJsonDocument>

bool Gazua::API::getOrders(std::shared_ptr<QMap<uint64_t, Order>> orders, const QString& coinName, const QVector<uint64_t>& ids, uint64_t limit){

    /*
    qUrl.addQueryItem("currency_pair", coinName);
    for(auto i = ids.begin(); i != ids.end(); i++)
        tmp.append(QString("id=%1&").arg(QString::number(*i)));
    tmp.chop(1);
    qUrl.addQueryItem("id", tmp);
    qUrl.addQueryItem("limit", QString::number(limit));

    if(!this->m_token.has_value())
        return false;
    const auto accessToken = this->m_token->accessToken();
    if(!accessToken.has_value())
        return false;

    const auto header = QString("Bearer %1").arg(accessToken.value());

    network.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    network.setUrl(qUrl.toString());
    */
    const auto accessToken = this->m_token->accessToken();
    if(!accessToken.has_value())
        return false;
    const auto header = QString("Bearer %1").arg(accessToken.value());

    QNetworkRequest network;
    network.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    network.setUrl(QUrl{"https://api.korbit.co.kr/v1/user/orders"});

    QNetworkReply* reply = m_qnam.get(network);
    connect(reply, &QNetworkReply::finished, this, [reply, orders]() {
        auto jsonArr =  QJsonDocument::fromJson(reply->readAll()).array();

        for(auto iter = jsonArr.begin(); iter != jsonArr.end(); iter++) {
            Order order;
            order.currency_pair = (*iter).toObject()["currency_pair"].toString();
            order.side = (*iter).toObject()["side"].toString();
            order.avg_price = (*iter).toObject()["avg_price"].toInt();
            order.price = (*iter).toObject()["price"].toInt();
            order.order_amount = (*iter).toObject()["order_amount"].toDouble();
            order.filled_amount = (*iter).toObject()["filled_amount"].toDouble();
            order.order_total = (*iter).toObject()["order_total"].toInt();
            order.filled_total = (*iter).toObject()["filled_total"].toInt();
            order.created_at = (*iter).toObject()["created_at"].toInt();
            order.last_filled_at = (*iter).toObject()["last_filled_at"].toInt();
            order.status = (*iter).toObject()["status"].toString();
            order.fee = (*iter).toObject()["fee"].toDouble();

            orders->insert((*iter).toObject()["id"].toInt(), order);
        }
        reply->close();
    });

    return true;
}
