from __future__ import annotations

from abc import ABC, abstractmethod

from techtest.models.trade import Trade


class TradeReceiver(ABC):
    @abstractmethod
    def add(self, trade: Trade) -> None:
        ...
