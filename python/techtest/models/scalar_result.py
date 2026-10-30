from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class ScalarResult:
    trade_id: str
    result: float | None
    error: str | None

    def __post_init__(self) -> None:
        if self.trade_id is None or not self.trade_id.strip():
            raise ValueError("A non null, non empty trade id must be provided")
