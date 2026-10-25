from __future__ import annotations

from techtest.models.i_trade import ITrade
from techtest.models.i_trade_enumerable import ITradeEnumerable


class ITrades(ITradeEnumerable[ITrade]):
    pass
