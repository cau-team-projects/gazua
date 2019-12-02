#include "API.h"

Gazua::Order::Order(QString _currency_pair, QString _side, uint64_t _avg_price, uint64_t _price, long double _order_amount,
                    long double _filled_amount, uint64_t _order_total, uint64_t _filled_total, uint64_t _created_at,
                    uint64_t _last_filled_at, QString _status, long double _fee){
    currency_pair=_currency_pair;
    side = _side;
    avg_price = _avg_price;
    price = _price;
    order_amount = _order_amount;
    filled_amount = _filled_amount;
    order_total = _order_total;
    filled_total = _filled_total;
    created_at = _created_at;
    last_filled_at = _last_filled_at;
    status = _status;
    fee = _fee;
}
