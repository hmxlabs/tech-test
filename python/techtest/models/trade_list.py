from __future__ import annotations

from typing import Iterable, Optional

from techtest.models.i_trade import ITrade
from techtest.models.i_trade_receiver import ITradeReceiver


class TradeList(list, ITradeReceiver):
    """A list of trades that can also receive trades."""

    def __init__(self, trades: Optional[Iterable[ITrade]] = None) -> None:
        super().__init__()
        if trades is not None:
            self.extend(trades)

    def add(self, trade: ITrade) -> None:
        self.append(trade)

    def add_trades(self, trades: Iterable[ITrade]) -> None:
        self.extend(trades)
