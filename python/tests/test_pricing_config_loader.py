import os
import unittest

from techtest.models import BondTrade, FxTrade
from techtest.risk_system import PRICING_CONFIG_DIR, PricingConfigLoader


class PricingConfigLoaderTests(unittest.TestCase):
    def setUp(self):
        loader = PricingConfigLoader()
        loader.config_file = os.path.join(PRICING_CONFIG_DIR, "PricingEngines.xml")
        self.config = loader.load_config()

    def test_config_item_count(self):
        self.assertEqual(len(self.config), 4)

    def test_first_config_mapping(self):
        config_item = self.config[0]

        self.assertEqual(config_item.trade_type, BondTrade.GOV_BOND_TRADE_TYPE)
        self.assertEqual(config_item.type_name, "techtest.pricers.GovBondPricingEngine")
        self.assertEqual(config_item.assembly, "techtest.pricers")

    def test_last_config_mapping(self):
        config_item = self.config[3]
        self.assertEqual(config_item.trade_type, FxTrade.FX_FORWARD_TRADE_TYPE)
        self.assertEqual(config_item.type_name, "techtest.pricers.FxPricingEngine")
        self.assertEqual(config_item.assembly, "techtest.pricers")


if __name__ == "__main__":
    unittest.main()
