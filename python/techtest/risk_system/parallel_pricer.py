from __future__ import annotations

from typing import Iterable

from techtest.models import PricingEngine, ResultReceiver, Trade


class ParallelPricer:
    def __init__(self) -> None:
        self._pricers: dict[str, PricingEngine] = {}

    def price(self, trade_containers: Iterable[Iterable[Trade]], result_receiver: ResultReceiver) -> None:
        raise NotImplementedError()

    def _load_pricers(self) -> None:
        raise NotImplementedError()
