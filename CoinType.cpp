#include "API.h"
#include <QVector>
#include <QString>

namespace Gazua {
    class CoinType;
};

class CoinType {
public:
    static const QVector<QString> coinType;
};

const QVector<QString> Gazua::CoinType::coinType = {
    "bch_krw",
    "fet_krw",
    "bnb_krw",
    "loom_krw",
    "dai_krw",
    "zil_krw",
    "mkr_krw",
    "xlm_krw",
    "usdc_krw",
    "med_krw",
    "btc_krw",
    "bat_krw",
    "gnt_krw",
    "poly_krw",
    "aergo_krw",
    "bsv_krw",
    "eth_krw",
    "knc_krw",
    "snt_krw",
    "zrx_krw",
    "eos_krw",
    "xrp_krw",
    "link_krw",
    "qtum_krw",
    "btc_usdc",
    "etc_krw",
    "trx_krw",
    "omg_krw",
    "ltc_krw"
};
