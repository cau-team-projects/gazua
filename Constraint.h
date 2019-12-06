#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <QtGlobal>

namespace Gazua {
    struct Constraint;
};

struct Gazua::Constraint {
    qreal tick_size;
    qreal min_price;
    qreal max_price;
    qreal order_min_price;
    qreal order_max_price;
};

#endif
