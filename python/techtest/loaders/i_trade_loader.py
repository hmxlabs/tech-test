from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Iterable, Optional

from techtest.models import ITrade


class ITradeLoader(ABC):
    @abstractmethod
    def load_trades(self) -> Iterable[ITrade]:
        ...

    @property
    @abstractmethod
    def data_file(self) -> Optional[str]:
        ...

    @data_file.setter
    @abstractmethod
    def data_file(self, value: Optional[str]) -> None:
        ...
