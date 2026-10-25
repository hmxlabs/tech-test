from techtest.pricers.base_pricing_engine import BasePricingEngine


class CorpBondPricingEngine(BasePricingEngine):
    def __init__(self) -> None:
        super().__init__()
        self.delay = 8000
        self._add_supported_trade_type("CorpBond")
