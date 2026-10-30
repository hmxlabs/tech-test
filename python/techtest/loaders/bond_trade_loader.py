from __future__ import annotations

from datetime import datetime
from typing import Iterable

from techtest.models import BondTrade, BondTradeList, Trade


class BondTradeLoader:
    _SEPARATOR = ","

    def __init__(self, data_file: str) -> None:
        self.data_file = data_file

    def load_trades(self) -> Iterable[Trade]:
        trade_list = BondTradeList()
        self._load_trades_from_file(self.data_file, trade_list)

        return trade_list

    def _create_trade_from_line(self, line: str) -> BondTrade:
        items = line.split(self._SEPARATOR)
        trade = BondTrade(items[6])
        trade.trade_date = datetime.fromisoformat(items[1])
        trade.instrument = items[2]
        trade.counterparty = items[3]
        trade.notional = float(items[4])
        trade.rate = float(items[5])

        return trade

    def _load_trades_from_file(self, filename: str, trade_list: BondTradeList) -> None:
        # utf-8-sig skips the byte order mark at the start of the file
        with open(filename, encoding="utf-8-sig") as stream:
            next(stream, None)  # Skip the header line
            for line in stream:
                trade_list.add(self._create_trade_from_line(line.rstrip("\r\n")))
