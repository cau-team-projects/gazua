#include "API.h"

Gazua::CoinInfo::CoinInfo()
{
    timestamp = 0.0;
    last = 0.0;
    open = 0.0;
    bid = 0.0;
    ask = 0.0;
    low = 0.0;
    high = 0.0;
    volume = 0.0;
    change = 0.0;
    changePercent = 0.0;
    tick_size = 0.0;
    min_price = 0.0;
    max_price = 0.0;
    order_min_size = 0.0;
    order_max_size = 0.0;
}


Gazua::CoinInfo::CoinInfo(double _timestamp, double _last, double _open, double _bid, double _ask, double _low, double _high, double _volume, double _change, double _changePercent, double _tick_size, double _min_price, double _max_price, double _order_min_size, double _order_max_size)
{
    timestamp = (long long)_timestamp;
    last = _last;
    open = _open;
    bid = _bid;
    ask = _ask;
    low = _low;
    high = _high;
    volume = _volume;
    change = _change;
    changePercent = _changePercent;
    tick_size = _tick_size;
    min_price = _min_price;
    max_price = _max_price;
    order_min_size = _order_min_size;
    order_max_size = _order_max_size;
}
