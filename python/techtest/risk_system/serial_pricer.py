from __future__ import annotations

import os
from typing import Iterable

from techtest.models import PricingEngine, ResultReceiver, Trade
from techtest.risk_system.pricing_config_loader import PricingConfigLoader


class SerialPricer:
    def __init__(self) -> None:
        self._pricers: dict[str, PricingEngine] = {}

    def price(self, trade_containers: Iterable[Iterable[Trade]], result_receiver: ResultReceiver) -> None:
        self._load_pricers()

        for trade_container in trade_containers:
            for trade in trade_container:
                if trade.trade_type not in self._pricers:
                    result_receiver.add_error(trade.trade_id, "No Pricing Engines available for this trade type")
                    continue

                pricer = self._pricers[trade.trade_type]
                pricer.price(trade, result_receiver)

    def _load_pricers(self) -> None:
        pricing_config_loader = PricingConfigLoader()
        pricing_config_loader.config_file = os.path.join(
            os.path.dirname(os.path.abspath(__file__)), "pricing_config", "PricingEngines.xml")
        pricer_config = pricing_config_loader.load_config()

        for config_item in pricer_config:
            raise NotImplementedError()
