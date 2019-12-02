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
#include "AmountType.h"
#include "CoinInfo.h"
#include "CoinType.h"
#include "Order.h"
#include "OrderType.h"
#include "Token.h"
#include "TokenType.h"
#include "UserInfo.h"

namespace Gazua {
    class API;
};

class Gazua::API : public QObject {
    Q_OBJECT
private:
    std::optional<Token> m_token;
    QNetworkAccessManager m_qnam;

public:
    explicit API();
    bool access(const QString& key, const QString& secret);
    bool refresh();
    // GET https://api.korbit.co.kr/v1/ticker/detailed/all
    // GET https://api.korbit.co.kr/v1/constants
    bool refreshCoinInfos(std::shared_ptr<QMap<QString, CoinInfo>> coinInfos);

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
    bool getOrders(std::shared_ptr<QMap<uint64_t, Order>> orders, const QString& coinName, const QVector<uint64_t>& ids, uint64_t limit = 10);
};

#endif
