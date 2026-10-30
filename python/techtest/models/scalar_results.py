from __future__ import annotations

from typing import Iterator

from techtest.models.result_receiver import ResultReceiver
from techtest.models.scalar_result import ScalarResult


class ScalarResults(ResultReceiver):
    """Pricing results and errors by trade ID. Iterating over it should give one ScalarResult per trade."""

    def __init__(self) -> None:
        self._results: dict[str, float] = {}
        self._errors: dict[str, str | None] = {}

    def __getitem__(self, trade_id: str) -> ScalarResult:
        if trade_id not in self:
            raise KeyError(trade_id)

        return ScalarResult(trade_id, self._results.get(trade_id), self._errors.get(trade_id))

    def get(self, trade_id: str) -> ScalarResult | None:
        if trade_id not in self:
            return None

        return self[trade_id]

    def __contains__(self, trade_id: object) -> bool:
        return trade_id in self._results or trade_id in self._errors

    def add_result(self, trade_id: str, result: float) -> None:
        # Adding a second result for the same trade is an error
        if trade_id in self._results:
            raise ValueError("A result has already been added for trade " + trade_id)
        self._results[trade_id] = result

    def add_error(self, trade_id: str, error: str | None) -> None:
        if trade_id in self._errors:
            raise ValueError("An error has already been added for trade " + trade_id)
        self._errors[trade_id] = error

    def __iter__(self) -> Iterator[ScalarResult]:
        raise NotImplementedError()
