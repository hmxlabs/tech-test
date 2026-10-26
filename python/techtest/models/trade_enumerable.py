from __future__ import annotations

from abc import ABC
from typing import Generic, Iterable, TypeVar

from techtest.models.trade import Trade

T = TypeVar("T", bound=Trade)


class TradeEnumerable(Iterable[T], Generic[T], ABC):
    """An iterable of trades of type T."""
