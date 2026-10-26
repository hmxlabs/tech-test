from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Iterable

from techtest.models import Trade


class TradeLoader(ABC):
    def __init__(self, data_file: str) -> None:
        self.data_file = data_file

    @abstractmethod
    def load_trades(self) -> Iterable[Trade]:
        ...
