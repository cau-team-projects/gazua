#ifndef API_H
#define API_H

#include <map>
#include <memory>
#include <optional>
#include <QVector>
#include <QMap>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QTableView>
#include "AmountType.h"
#include "Order.h"
#include "OrderModel.h"
#include "OrderType.h"
#include "Token.h"
#include "TokenType.h"
#include "CoinInfo.h"
#include "UserInfo.h"

namespace Gazua {
    class API;
};

class Gazua::API : public QObject {
    Q_OBJECT
private:
    QString m_key;
    QString m_secret;
    std::optional<Token> m_token;
    QNetworkAccessManager m_qnam;

public:
    explicit API(QString&& key, QString&& secret);
    bool access();
    bool refresh();
    // GET https://api.korbit.co.kr/v1/ticker/detailed/all
    // GET https://api.korbit.co.kr/v1/constants
    bool refreshCoinInfo(std::shared_ptr<CoinInfo> coinInfo);

    // GET https://api.korbit.co.kr/v1/user/balances
    // GET https://api.korbit.co.kr/v1/user/volume
    bool refreshUserInfo(std::shared_ptr<UserInfo> userInfo);

    // POST https://api.korbit.co.kr/v1/user/orders/buy
    bool buy(const QString& coinName, OrderType orderType, uint64_t price, AmountType amountType, uint64_t amount);
    // POST https://api.korbit.co.kr/v1/user/orders/sell
    bool sell(const QString& coinName, OrderType orderType, uint64_t price, uint64_t amount);

    // POST https://api.korbit.co.kr/v1/user/orders/cancel
    bool cancel(const QString& coinName, const QVector<uint64_t>& ids);

    // GET https://api.korbit.co.kr/v1/user/orders
    bool getOrders(std::shared_ptr<OrderModel> orderModel);
};

#endif
