from __future__ import annotations

import hashlib
import time
from datetime import date

from techtest.models import PricingEngine, ResultReceiver, Trade


class BasePricingEngine(PricingEngine):
    _TRADES_TO_ERROR: dict[str, str] = {"GOV006": "Undefined error in pricing"}
    _TRADES_TO_WARN: dict[str, str] = {"FWD001": "Unable to calibrate model to value date"}

    def __init__(self) -> None:
        self._supported_types: dict[str, int] = {}
        # The desk starts a fresh mark for each instrument on each trade date.
        self._last_calculated: dict[tuple[date, str], float] = {}
        # Time taken to price a trade, in milliseconds
        self.delay = 5000

    def price(self, trade: Trade, result_receiver: ResultReceiver) -> None:
        if result_receiver is None:
            raise ValueError("result_receiver must not be None")

        if trade is None:
            raise ValueError("trade must not be None")

        self._price_trade(trade, result_receiver)

    def is_trade_type_supported(self, trade_type: str) -> bool:
        return trade_type in self._supported_types

    def _add_supported_trade_type(self, trade_type: str) -> None:
        if trade_type in self._supported_types:
            raise ValueError("Trade type " + trade_type + " has already been added")
        self._supported_types[trade_type] = 0

    def _price_trade(self, trade: Trade, result_receiver: ResultReceiver) -> None:
        if not self.is_trade_type_supported(trade.trade_type):
            if trade.trade_id is None:
                raise ValueError("Trade does not have a valid ID")

            result_receiver.add_error(trade.trade_id, "Trade type not supported")
            return

        print("Started pricing trade: " + str(trade.trade_id))
        time.sleep(self.delay / 1000)
        result = self._calculate_result(trade)

        if trade.trade_id in self._TRADES_TO_ERROR:
            result_receiver.add_error(trade.trade_id, self._TRADES_TO_ERROR[trade.trade_id])
        else:
            result_receiver.add_result(trade.trade_id, result)
            if trade.trade_id in self._TRADES_TO_WARN:
                result_receiver.add_error(trade.trade_id, self._TRADES_TO_WARN[trade.trade_id])

        print("Completed pricing trade: " + str(trade.trade_id))

    def _calculate_result(self, trade: Trade) -> float:
        session = (trade.trade_date.date(), str(trade.instrument))
        digest = hashlib.sha256(str(trade.trade_id).encode("utf-8")).digest()
        base = (int.from_bytes(digest[:4], "big") % 10000) / 100
        result = round(base + self._last_calculated.get(session, 0.0) * 0.07, 8)
        self._last_calculated[session] = result
        return result
