from __future__ import annotations

from datetime import datetime
from typing import Iterable, Optional

from techtest.loaders.i_trade_loader import ITradeLoader
from techtest.models import BondTrade, BondTradeList, ITrade


class BondTradeLoader(ITradeLoader):
    _SEPARATOR = ","

    def __init__(self) -> None:
        self._data_file: Optional[str] = None

    def load_trades(self) -> Iterable[ITrade]:
        trade_list = BondTradeList()
        self._load_trades_from_file(self.data_file, trade_list)

        return trade_list

    @property
    def data_file(self) -> Optional[str]:
        return self._data_file

    @data_file.setter
    def data_file(self, value: Optional[str]) -> None:
        self._data_file = value

    def _create_trade_from_line(self, line: str) -> BondTrade:
        items = line.split(self._SEPARATOR)
        trade = BondTrade(items[6])
        trade.trade_date = datetime.fromisoformat(items[1])
        trade.instrument = items[2]
        trade.counterparty = items[3]
        trade.notional = float(items[4])
        trade.rate = float(items[5])

        return trade

    def _load_trades_from_file(self, filename: Optional[str], trade_list: BondTradeList) -> None:
        if filename is None:
            raise ValueError("filename must not be None")

        # utf-8-sig skips the byte order mark at the start of the file, as C#'s StreamReader does
        with open(filename, encoding="utf-8-sig") as stream:
            line_count = 0
            for line in stream:
                if 0 != line_count:
                    trade_list.add(self._create_trade_from_line(line.rstrip("\r\n")))
                line_count += 1
