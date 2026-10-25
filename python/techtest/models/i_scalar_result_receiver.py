from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Optional


class IScalarResultReceiver(ABC):
    @abstractmethod
    def add_result(self, trade_id: str, result: float) -> None:
        ...

    @abstractmethod
    def add_error(self, trade_id: str, error: Optional[str]) -> None:
        ...
