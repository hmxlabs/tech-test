from __future__ import annotations

from techtest.models.base_trade import BaseTrade


class BondTrade(BaseTrade):
    GOV_BOND_TRADE_TYPE = "GovBond"
    CORP_BOND_TRADE_TYPE = "CorpBond"

    def __init__(self, trade_id: str, trade_type: str = GOV_BOND_TRADE_TYPE) -> None:
        super().__init__()
        if trade_id is None or not trade_id.strip():
            raise ValueError("A valid non null, non empty trade ID must be provided")

        self._trade_id = trade_id
        self._trade_type = (
            self.CORP_BOND_TRADE_TYPE
            if trade_type == self.CORP_BOND_TRADE_TYPE
            else self.GOV_BOND_TRADE_TYPE
        )

    @property
    def trade_type(self) -> str:
        return self._trade_type
