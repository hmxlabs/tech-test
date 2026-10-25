from __future__ import annotations

from abc import ABC, abstractmethod

from techtest.models.i_scalar_result_receiver import IScalarResultReceiver
from techtest.models.i_trade import ITrade


class IPricingEngine(ABC):
    @abstractmethod
    def price(self, trade: ITrade, result_receiver: IScalarResultReceiver) -> None:
        ...
