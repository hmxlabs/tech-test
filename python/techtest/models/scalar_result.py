from __future__ import annotations

from typing import Optional


class ScalarResult:
    def __init__(self, trade_id: str, result: Optional[float], error: Optional[str]) -> None:
        if trade_id is None or not trade_id.strip():
            raise ValueError("A non null, non empty trade id must be provided")

        self._trade_id = trade_id
        self._result = result
        self._error = error

    @property
    def trade_id(self) -> str:
        return self._trade_id

    @property
    def result(self) -> Optional[float]:
        return self._result

    @property
    def error(self) -> Optional[str]:
        return self._error
