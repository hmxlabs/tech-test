from __future__ import annotations

from techtest.models import ScalarResults
from techtest.risk_system import ScreenResultPrinter, SerialPricer, SerialTradeLoader


def main() -> None:
    trade_loader = SerialTradeLoader()

    all_trades = trade_loader.load_trades()
    results = ScalarResults()
    pricer = SerialPricer()
    pricer.price(all_trades, results)

    screen_printer = ScreenResultPrinter()
    screen_printer.print_results(results)

    input("Press Enter to exit..")


if __name__ == "__main__":
    main()
