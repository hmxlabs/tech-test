import hashlib
import tempfile
import tracemalloc
import unittest
from pathlib import Path

from techtest.loaders import BondTradeLoader, FxTradeLoader


BOND_HEADER = "Type,TradeDate,Instrument,Counterparty,Notional,Rate,TradeId"
FX_HEADER = "Type¬TradeDate¬Ccy1¬Ccy2¬Amount¬Rate¬ValueDate¬Counterparty¬TradeId"


class FeedIntegrityTests(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.directory = Path(directory.name)

    def write_feed(self, name, header_lines, row, separator, count, digest):
        path = self.directory / name
        path.write_text("\n".join([*header_lines, row, f"END{separator}{count}{separator}{digest}"]) + "\n",
                        encoding="utf-8")
        return str(path)

    def assert_releases_nothing(self, loader):
        emitted = 0
        with self.assertRaises(ValueError):
            for _ in loader.load_trades():
                emitted += 1
        self.assertEqual(emitted, 0)

    def test_invalid_bond_checksum_releases_nothing(self):
        row = "GovBond,2012-04-17,ABC,CSI,100,105,GOV001"
        path = self.write_feed("bond.dat", [BOND_HEADER], row, ",", 2, "0" * 64)
        self.assert_releases_nothing(BondTradeLoader(path))

    def test_invalid_fx_count_releases_nothing(self):
        row = "FxSpot¬2012-10-08¬EUR¬USD¬100¬1.0¬2012-10-11¬CSI¬SPOT001"
        digest = hashlib.sha256((row + "\n").encode("utf-8")).hexdigest()
        path = self.write_feed("fx.dat", ["FxTrades¬2012-10-15", FX_HEADER], row, "¬", 99, digest)
        self.assert_releases_nothing(FxTradeLoader(path))

    def test_large_valid_feed_does_not_accumulate_trades(self):
        path = self.directory / "large_bond.dat"
        digest = hashlib.sha256()
        with path.open("w", encoding="utf-8") as stream:
            stream.write(BOND_HEADER + "\n")
            for index in range(10000):
                row = f"GovBond,2012-04-17,ABC,CSI,100,105,GOV{index:05d}\n"
                stream.write(row)
                digest.update(row.encode("utf-8"))
            stream.write(f"END,10001,{digest.hexdigest()}\n")
        tracemalloc.start()
        try:
            count = sum(1 for _ in BondTradeLoader(str(path)).load_trades())
            _, peak = tracemalloc.get_traced_memory()
        finally:
            tracemalloc.stop()
        self.assertEqual(count, 10000)
        self.assertLess(peak, 2_000_000)


if __name__ == "__main__":
    unittest.main()
