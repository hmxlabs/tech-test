from __future__ import annotations

from abc import ABC, abstractmethod
from datetime import datetime


class Trade(ABC):
    """A trade. trade_date, instrument, counterparty, notional and rate are read/write attributes."""

    trade_date: datetime
    instrument: str | None
    counterparty: str | None
    notional: float
    rate: float

    @property
    @abstractmethod
    def trade_type(self) -> str:
        ...

    @property
    @abstractmethod
    def trade_id(self) -> str:
        ...
