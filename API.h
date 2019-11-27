#ifndef API_H
#define API_H

#include <map>
#include <memory>
#include <optional>
#include <vector>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QObject>

#include "AmountType.h"
#include "CoinInfo.h"
#include "Order.h"
#include "OrderType.h"
#include "Token.h"
#include "UserInfo.h"

namespace Gazua {
    class API;
};

class Gazua::API : public QObject {
    Q_OBJECT
private:
    std::optional<Token> m_token;
    QNetworkAccessManager m_qnam;
    QNetworkReply* m_accessReply;
    QNetworkReply* m_refreshReply;
    QNetworkReply* m_refreshCoinInfosReply;
    QNetworkReply* m_buyReply;
    QNetworkReply* m_sellReply;
    QNetworkReply* m_cancelReply;
    QNetworkReply* m_getOrdersReply;

public:
    explicit API();
    bool access(const std::string& key, const std::string& secret);
    bool refresh();
    // GET https://api.korbit.co.kr/v1/ticker/detailed/all
    // GET https://api.korbit.co.kr/v1/constants
    bool refreshCoinInfos(std::shared_ptr<std::unordered_map<std::string, CoinInfo>> coinInfos);

    // GET https://api.korbit.co.kr/v1/user/balances
    // GET https://api.korbit.co.kr/v1/user/volume
    bool refreshUserInfo(std::shared_ptr<UserInfo> userInfo);

    // POST https://api.korbit.co.kr/v1/user/orders/buy
    bool buy(const std::string& coinName, OrderType orderType, uint64_t price, AmountType amountType, uint64_t amount);
    // POST https://api.korbit.co.kr/v1/user/orders/sell
    bool sell(const std::string& coinName, OrderType orderType, uint64_t price, uint64_t amount);

    // POST https://api.korbit.co.kr/v1/user/orders/cancel
    bool cancel(const std::string& coinName, const std::vector<uint64_t>& ids);

    // GET https://api.korbit.co.kr/v1/user/orders
    bool getOrders(std::shared_ptr<std::map<uint64_t, Order>> orders, const std::string& coinName, const std::vector<uint64_t>& ids, uint64_t limit = 10);

public slots:
    void accessFinished();
};

#endif
