from __future__ import annotations

import os
from typing import Iterable

from techtest.loaders import TRADE_DATA_DIR, BondTradeLoader, FxTradeLoader, TradeLoader
from techtest.models import Trade


class SerialTradeLoader:
    def load_trades(self) -> Iterable[Iterable[Trade]]:
        loaders = self._get_trade_loaders()

        return [loader.load_trades() for loader in loaders]

    def _get_trade_loaders(self) -> Iterable[TradeLoader]:
        return [
            BondTradeLoader(os.path.join(TRADE_DATA_DIR, "BondTrades.dat")),
            FxTradeLoader(os.path.join(TRADE_DATA_DIR, "FxTrades.dat")),
        ]
