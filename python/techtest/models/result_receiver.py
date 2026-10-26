from __future__ import annotations

from abc import ABC, abstractmethod


class ResultReceiver(ABC):
    @abstractmethod
    def add_result(self, trade_id: str, result: float) -> None:
        ...

    @abstractmethod
    def add_error(self, trade_id: str, error: str | None) -> None:
        ...
