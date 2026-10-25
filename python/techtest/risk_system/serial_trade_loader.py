from __future__ import annotations

import os
from typing import Iterable, List

from techtest.loaders import TRADE_DATA_DIR, BondTradeLoader, FxTradeLoader, ITradeLoader
from techtest.models import ITrade


class SerialTradeLoader:
    def load_trades(self) -> Iterable[Iterable[ITrade]]:
        loaders = self._get_trade_loaders()

        return [loader.load_trades() for loader in loaders]

    def _get_trade_loaders(self) -> Iterable[ITradeLoader]:
        loaders: List[ITradeLoader] = []
        loader: ITradeLoader = BondTradeLoader()
        loader.data_file = os.path.join(TRADE_DATA_DIR, "BondTrades.dat")
        loaders.append(loader)

        loader = FxTradeLoader()
        loader.data_file = os.path.join(TRADE_DATA_DIR, "FxTrades.dat")
        loaders.append(loader)

        return loaders
