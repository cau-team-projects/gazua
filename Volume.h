#ifndef VOLUME_H
#define VOLUME_H

#include <QtGlobal>

struct Volume {
    quint64 volume; // 해당 통화쌍의 30일간의 거래량(KRW).
    qreal maker_fee; // 베이시스 포인트(BPS - 1/100 퍼센트 기준)로 표기된 maker 거래 수수료율.
    qreal taker_fee; // 베이시스 포인트(BPS - 1/100 퍼센트 기준)로 표기된 taker 거래 수수료율.
};

#endif
