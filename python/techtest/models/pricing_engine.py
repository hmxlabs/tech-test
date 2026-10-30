from __future__ import annotations

from abc import ABC, abstractmethod

from techtest.models.result_receiver import ResultReceiver
from techtest.models.trade import Trade


class PricingEngine(ABC):
    @abstractmethod
    def price(self, trade: Trade, result_receiver: ResultReceiver) -> None:
        ...
