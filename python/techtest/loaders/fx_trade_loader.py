from __future__ import annotations

from typing import Iterable, Optional

from techtest.loaders.i_trade_loader import ITradeLoader
from techtest.models import ITrade


class FxTradeLoader(ITradeLoader):
    # NOTE: These methods are only here to allow the solution to run prior to the test being completed.
    def load_trades(self) -> Iterable[ITrade]:
        raise NotImplementedError()

    @property
    def data_file(self) -> Optional[str]:
        raise NotImplementedError()

    @data_file.setter
    def data_file(self, value: Optional[str]) -> None:
        raise NotImplementedError()
