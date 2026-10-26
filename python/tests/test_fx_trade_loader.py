import os
import unittest
from datetime import datetime

from techtest.loaders import TRADE_DATA_DIR, FxTradeLoader
from techtest.models import FxTrade, TradeList


class FxTradeLoaderTests(unittest.TestCase):
    def setUp(self):
        loader = FxTradeLoader(os.path.join(TRADE_DATA_DIR, "FxTrades.dat"))
        trades = loader.load_trades()
        self.trade_list = TradeList(trades)

    def test_trade_load_count(self):
        self.assertEqual(len(self.trade_list), 4)

    def test_trade_load_accuracy_of_first_trade(self):
        self.assertIs(type(self.trade_list[0]), FxTrade)

        trade = self.trade_list[0]
        self.assertEqual(trade.trade_type, FxTrade.FX_SPOT_TRADE_TYPE)
        self.assertEqual(trade.trade_date, datetime(2012, 10, 8))
        self.assertEqual(trade.instrument, "EURUSD")
        self.assertEqual(trade.counterparty, "CSI,AG")
        self.assertEqual(trade.notional, 145000000)
        self.assertEqual(trade.rate, 0.97562)
        self.assertEqual(trade.value_date, datetime(2012, 10, 11))

    def test_trade_load_accuracy_of_last_trade(self):
        self.assertIs(type(self.trade_list[3]), FxTrade)

        trade = self.trade_list[3]
        self.assertEqual(trade.trade_type, FxTrade.FX_FORWARD_TRADE_TYPE)
        self.assertEqual(trade.trade_date, datetime(2012, 5, 9))
        self.assertEqual(trade.instrument, "USDJPY")
        self.assertEqual(trade.counterparty, "GS")
        self.assertEqual(trade.notional, 1223445000)
        self.assertEqual(trade.rate, 78.983)
        self.assertEqual(trade.value_date, datetime(2012, 7, 16))


if __name__ == "__main__":
    unittest.main()
