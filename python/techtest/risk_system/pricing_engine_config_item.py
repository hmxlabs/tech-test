from __future__ import annotations

from typing import Optional


class PricingEngineConfigItem:
    def __init__(self) -> None:
        self.trade_type: Optional[str] = None
        # The module the pricing engine lives in (the C# version names a .NET assembly)
        self.assembly: Optional[str] = None
        # The pricing engine class's full name, e.g. "techtest.pricers.GovBondPricingEngine"
        self.type_name: Optional[str] = None
