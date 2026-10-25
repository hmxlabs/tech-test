from __future__ import annotations

from abc import abstractmethod
from datetime import datetime
from typing import Optional

from techtest.models.i_trade import ITrade


class BaseTrade(ITrade):
    def __init__(self) -> None:
        self.trade_date: datetime = datetime.min
        self.counterparty: Optional[str] = None
        self.instrument: Optional[str] = None
        self.notional: float = 0.0
        self.rate: float = 0.0
        # Set by subclasses (the C# setter is protected)
        self._trade_id: Optional[str] = None

    @property
    @abstractmethod
    def trade_type(self) -> str:
        ...

    @property
    def trade_id(self) -> Optional[str]:
        return self._trade_id
