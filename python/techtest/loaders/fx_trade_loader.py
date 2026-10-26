from __future__ import annotations

from typing import Iterable

from techtest.loaders.trade_loader import TradeLoader
from techtest.models import Trade


class FxTradeLoader(TradeLoader):
    # NOTE: This method is only here to allow the solution to run prior to the test being completed.
    def load_trades(self) -> Iterable[Trade]:
        raise NotImplementedError()
