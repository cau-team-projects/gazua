#ifndef COIN_TYPE_H
#define COIN_TYPE_H

#include <string>
#include <QVector>

namespace Gazua {
    class CoinType;
};

class Gazua::CoinType {
public:
    static const QVector<std::string> coin_type;
};

#endif
