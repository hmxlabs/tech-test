from __future__ import annotations

from datetime import datetime

from techtest.models.base_trade import BaseTrade


class FxTrade(BaseTrade):
    FX_SPOT_TRADE_TYPE = "FxSpot"
    FX_FORWARD_TRADE_TYPE = "FxFwd"

    def __init__(self, trade_id: str, trade_type: str) -> None:
        super().__init__()
        if trade_id is None or not trade_id.strip():
            raise ValueError("A valid non null, non empty trade ID must be provided")
        self._trade_id = trade_id
        self._trade_type = trade_type
        self.value_date: datetime = datetime.min

    @property
    def trade_type(self) -> str:
        return self._trade_type
