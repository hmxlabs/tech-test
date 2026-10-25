from __future__ import annotations

from abc import ABC, abstractmethod
from datetime import datetime
from typing import Optional


class ITrade(ABC):
    """A trade. trade_date, instrument, counterparty, notional and rate are read/write attributes."""

    trade_date: datetime
    instrument: Optional[str]
    counterparty: Optional[str]
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
