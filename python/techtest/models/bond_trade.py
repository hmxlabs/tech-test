from __future__ import annotations

from techtest.models.base_trade import BaseTrade


class BondTrade(BaseTrade):
    GOV_BOND_TRADE_TYPE = "GovBond"
    CORP_BOND_TRADE_TYPE = "CorpBond"

    def __init__(self, trade_id: str) -> None:
        super().__init__()
        if trade_id is None or not trade_id.strip():
            raise ValueError("A valid non null, non empty trade ID must be provided")

        self._trade_id = trade_id

    @property
    def trade_type(self) -> str:
        return BondTrade.GOV_BOND_TRADE_TYPE
