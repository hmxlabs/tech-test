from techtest.pricers.base_pricing_engine import BasePricingEngine


class GovBondPricingEngine(BasePricingEngine):
    def __init__(self) -> None:
        super().__init__()
        self.delay = 5000
        self._add_supported_trade_type("GovBond")
