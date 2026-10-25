from techtest.pricers.base_pricing_engine import BasePricingEngine


class FxPricingEngine(BasePricingEngine):
    def __init__(self) -> None:
        super().__init__()
        self.delay = 2000
        self._add_supported_trade_type("FxSpot")
        self._add_supported_trade_type("FxFwd")
