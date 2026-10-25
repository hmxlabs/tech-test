from __future__ import annotations

from typing import Dict, Iterator, Optional

from techtest.models.i_scalar_result_receiver import IScalarResultReceiver
from techtest.models.scalar_result import ScalarResult


class ScalarResults(IScalarResultReceiver):
    """Pricing results and errors by trade ID. Iterating over it should give one ScalarResult per trade."""

    def __init__(self) -> None:
        self._results: Dict[str, float] = {}
        self._errors: Dict[str, Optional[str]] = {}

    def __getitem__(self, trade_id: str) -> Optional[ScalarResult]:
        if not self.contains_trade(trade_id):
            return None

        price_result: Optional[float] = None
        error: Optional[str] = None
        if trade_id in self._results:
            price_result = self._results[trade_id]
        if trade_id in self._errors:
            error = self._errors[trade_id]

        return ScalarResult(trade_id, price_result, error)

    def contains_trade(self, trade_id: str) -> bool:
        if trade_id in self._results or trade_id in self._errors:
            return True

        return False

    def add_result(self, trade_id: str, result: float) -> None:
        # Like C#'s Dictionary.Add, adding a second result for the same trade is an error
        if trade_id in self._results:
            raise ValueError("A result has already been added for trade " + trade_id)
        self._results[trade_id] = result

    def add_error(self, trade_id: str, error: Optional[str]) -> None:
        if trade_id in self._errors:
            raise ValueError("An error has already been added for trade " + trade_id)
        self._errors[trade_id] = error

    def __iter__(self) -> Iterator[ScalarResult]:
        raise NotImplementedError()
