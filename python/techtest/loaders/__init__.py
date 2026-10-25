import os

from techtest.loaders.i_trade_loader import ITradeLoader
from techtest.loaders.bond_trade_loader import BondTradeLoader
from techtest.loaders.fx_trade_loader import FxTradeLoader

# The trade feed files that ship with the loaders (C# copies them to the output folder instead)
TRADE_DATA_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "trade_data")

__all__ = ["ITradeLoader", "BondTradeLoader", "FxTradeLoader", "TRADE_DATA_DIR"]
