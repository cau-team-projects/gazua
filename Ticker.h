#ifndef TICKER_H
#define TICKER_H

namespace Gazua {
    struct Ticker;
}

struct Gazua::Ticker {
    quint64 timestamp;
    qreal last;
    qreal open;
    qreal bid;
    qreal ask;
    qreal low;
    qreal high;
    qreal volume;
    qreal change;
    qreal changePercent;
};

#endif
