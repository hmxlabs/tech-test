import unittest

from techtest.models import BondTrade, FxTrade
from techtest.pricers import CorpBondPricingEngine, FxPricingEngine, GovBondPricingEngine


class PricingEngineTests(unittest.TestCase):
    def test_pricer_type_config(self):
        gov_bond_pricer = GovBondPricingEngine()
        self.assertTrue(gov_bond_pricer.is_trade_type_supported(BondTrade.GOV_BOND_TRADE_TYPE))

        corp_bond_pricer = CorpBondPricingEngine()
        self.assertTrue(corp_bond_pricer.is_trade_type_supported(BondTrade.CORP_BOND_TRADE_TYPE))

        fx_pricer = FxPricingEngine()
        self.assertTrue(fx_pricer.is_trade_type_supported(FxTrade.FX_SPOT_TRADE_TYPE))
        self.assertTrue(fx_pricer.is_trade_type_supported(FxTrade.FX_FORWARD_TRADE_TYPE))


if __name__ == "__main__":
    unittest.main()
