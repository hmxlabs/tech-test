from __future__ import annotations

from typing import Iterable

from techtest.models import Trade


class FxTradeLoader:
    def __init__(self, data_file: str) -> None:
        self.data_file = data_file

    # NOTE: This method is only here to allow the solution to run prior to the test being completed.
    def load_trades(self) -> Iterable[Trade]:
        raise NotImplementedError()
