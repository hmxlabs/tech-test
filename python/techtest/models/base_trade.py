from __future__ import annotations

from abc import abstractmethod
from datetime import datetime

from techtest.models.trade import Trade


class BaseTrade(Trade):
    def __init__(self) -> None:
        self.trade_date: datetime = datetime.min
        self.counterparty: str | None = None
        self.instrument: str | None = None
        self.notional: float = 0.0
        self.rate: float = 0.0
        # Set by subclasses
        self._trade_id: str | None = None

    @property
    @abstractmethod
    def trade_type(self) -> str:
        ...

    @property
    def trade_id(self) -> str | None:
        return self._trade_id
