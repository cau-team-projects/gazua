#ifndef API_H
#define API_H

#include <optional>

namespace Gazua {
    class API;
};

class Gazua::API {
private:
    std::optional<Token> token;
public:
    void access(const std::string& key, const std::string& secret);
    void refresh();
    // GET https://api.korbit.co.kr/v1/ticker/detailed/all
    // GET https://api.korbit.co.kr/v1/constants
    std::unordered_map<std::string, CoinInfo> refreshCoinInfos();
    // GET https://api.korbit.co.kr/v1/user/balances
    std::unordered_map<std::string, Balance> refreshBalances();
    // GET https://api.korbit.co.kr/v1/user/volume
    std::unordered_map<std::string, VolumeFee> refreshVolumeFees();
    // POST https://api.korbit.co.kr/v1/user/orders/buy
    bool buy(const std::string& coinName, OrderType orderType, uint64_t price, AmountType amountType, uint64_t amount);
    // POST https://api.korbit.co.kr/v1/user/orders/sell
    bool sell(const std::string& coinName, OrderType orderType, uint64_t price, uint64_t amount);
    // POST https://api.korbit.co.kr/v1/user/orders/cancel
    bool cancel(const std::string& coinName, const std::vector<uint64_t>& ids);
    // GET https://api.korbit.co.kr/v1/user/orders
    std::map<uint64_t, Order> getOrders(const std::string& coinName, const std::vector<uint64_t>& ids, uint64_t limit = 10);
};
