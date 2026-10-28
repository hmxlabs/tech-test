import contextlib
import io
import unittest
from itertools import chain
from unittest.mock import patch

from techtest.models import ScalarResults
from techtest.risk_system import SerialPricer, SerialTradeLoader


class MultiFileFeedTests(unittest.TestCase):
    def test_all_supplied_files_are_included_in_source_order(self):
        loaders = list(SerialTradeLoader()._get_trade_loaders())
        self.assertEqual(len(loaders), 5)
        self.assertEqual([loader.data_file.rsplit("/", 1)[-1] for loader in loaders], [
            "BondTrades.dat", "BondTrades_2.dat", "BondTrades_3.dat",
            "FxTrades.dat", "FxTrades_2.dat",
        ])
        trades = list(chain.from_iterable(SerialTradeLoader().load_trades()))
        self.assertEqual(len(trades), 30)
        self.assertEqual(trades[0].trade_id, "GOV001")
        self.assertEqual(trades[-1].trade_id, "FWD004")

    def test_questionable_rows_are_visible_in_results(self):
        results = ScalarResults()
        with patch("techtest.pricers.base_pricing_engine.time.sleep", return_value=None), \
                contextlib.redirect_stdout(io.StringIO()):
            SerialPricer().price(SerialTradeLoader().load_trades(), results)
        for trade_id in ("CORP004", "CORP005", "GOV009", "SPOT002", "SPOT003", "SPOT004", "FWD004"):
            self.assertIsNotNone(results[trade_id].error, trade_id)


if __name__ == "__main__":
    unittest.main()
