from __future__ import annotations

from typing import Iterable

from techtest.models.trade import Trade
from techtest.models.trade_receiver import TradeReceiver


class TradeList(list, TradeReceiver):
    """A list of trades that can also receive trades."""

    def __init__(self, trades: Iterable[Trade] | None = None) -> None:
        super().__init__()
        if trades is not None:
            self.extend(trades)

    def add(self, trade: Trade) -> None:
        self.append(trade)

    def add_trades(self, trades: Iterable[Trade]) -> None:
        self.extend(trades)
