from __future__ import annotations

from datetime import datetime
from typing import Iterable

from techtest.models import FxTrade, Trade, TradeList


class FxTradeLoader:
    def __init__(self, data_file: str) -> None:
        self.data_file = data_file

    def load_trades(self) -> Iterable[Trade]:
        trades = TradeList()
        with open(self.data_file, encoding="utf-8-sig") as stream:
            next(stream, None)  # Feed metadata
            next(stream, None)  # Column names
            for line in stream:
                items = line.rstrip("\r\n").split("¬")
                if items[0] == "END":
                    break
                trade = FxTrade(items[8], items[0])
                trade.trade_date = datetime.fromisoformat(items[1])
                trade.instrument = items[2] + items[3]
                trade.notional = float(items[4])
                trade.rate = float(items[5])
                trade.value_date = datetime.fromisoformat(items[6])
                trade.counterparty = items[7]
                trades.add(trade)
        return trades
