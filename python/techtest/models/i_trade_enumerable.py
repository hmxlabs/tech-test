from __future__ import annotations

from abc import ABC
from typing import Generic, Iterable, TypeVar

from techtest.models.i_trade import ITrade

T = TypeVar("T", bound=ITrade)


class ITradeEnumerable(Iterable[T], Generic[T], ABC):
    """An iterable of trades of type T."""
