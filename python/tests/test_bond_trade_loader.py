import os
import unittest
from datetime import datetime

from techtest.loaders import TRADE_DATA_DIR, BondTradeLoader
from techtest.models import BondTrade, TradeList


class BondTradeLoaderTests(unittest.TestCase):
    def setUp(self):
        loader = BondTradeLoader()
        loader.data_file = os.path.join(TRADE_DATA_DIR, "BondTrades.dat")
        trades = loader.load_trades()
        self.trade_list = TradeList(trades)

    def test_trade_load_count(self):
        self.assertEqual(len(self.trade_list), 10)

    def test_trade_load_accuracy_of_first_trade(self):
        self.assertIs(type(self.trade_list[0]), BondTrade)

        trade = self.trade_list[0]
        self.assertEqual(trade.trade_type, BondTrade.GOV_BOND_TRADE_TYPE)
        self.assertEqual(trade.trade_date, datetime(2012, 4, 17))
        self.assertEqual(trade.instrument, "DE0001117794")
        self.assertEqual(trade.counterparty, "CSI\u00acAG")
        self.assertEqual(trade.notional, 674500000)
        self.assertEqual(trade.rate, 105.985)
        self.assertEqual(trade.trade_id, "GOV001")

    def test_trade_load_accuracy_of_last_trade(self):
        self.assertIs(type(self.trade_list[8]), BondTrade)

        trade = self.trade_list[8]
        self.assertEqual(trade.trade_type, BondTrade.CORP_BOND_TRADE_TYPE)
        self.assertEqual(trade.trade_date, datetime(2012, 8, 30))
        self.assertEqual(trade.instrument, "XS0340495216")
        self.assertEqual(trade.counterparty, "BLKROCK")
        self.assertEqual(trade.notional, 67000000)
        self.assertEqual(trade.rate, 120.240)
        self.assertEqual(trade.trade_id, "CORP003")


if __name__ == "__main__":
    unittest.main()
