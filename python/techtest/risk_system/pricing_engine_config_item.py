from __future__ import annotations

from dataclasses import dataclass


@dataclass
class PricingEngineConfigItem:
    trade_type: str
    # The module the pricing engine lives in, e.g. "techtest.pricers"
    module: str
    # The pricing engine's class name within that module, e.g. "GovBondPricingEngine"
    class_name: str
