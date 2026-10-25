from __future__ import annotations

from abc import ABC, abstractmethod

from techtest.models.i_trade import ITrade


class ITradeReceiver(ABC):
    @abstractmethod
    def add(self, trade: ITrade) -> None:
        ...
