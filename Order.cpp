#include "API.h"

Gazua::Order::Order(QString& _currency_pair, QString& _side, quint64 _avg_price, quint64 _price, qreal _order_amount,
                    qreal _filled_amount, quint64 _order_total, quint64 _filled_total, quint64 _created_at,
                    quint64 _last_filled_at, QString& _status, qreal _fee){
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
