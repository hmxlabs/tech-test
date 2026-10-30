from __future__ import annotations

from techtest.models import ScalarResults


class ScreenResultPrinter:
    def print_results(self, results: ScalarResults) -> None:
        for result in results:
            # Write code here to print out the results such that we have :
            # TradeID : Result : Error
            # If there is no result then the output should be :
            # TradeID : Error
            # If there is no error the output should be :
            # TradeID : Result
            pass
