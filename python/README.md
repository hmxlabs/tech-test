# Risk system tech test (Python)

A Python port of the [C# tech test](../c-sharp). The exercises are in [candidate-instructions.md](./candidate-instructions.md).

## Requirements

Python 3.9 or later. Only the Python standard library is used: there is nothing to install.

## Running the tests

From this folder:

```
python3 -m unittest discover -s tests -t .
```

As provided, some tests fail or error. Completing the exercises makes them pass.

## Running the application

From this folder:

```
python3 -m techtest.console_app
```

## Layout

Each C# project is a package under `techtest`:

| C# project | Python package |
|---|---|
| Models | `techtest/models` |
| Loaders (and `TradeData`) | `techtest/loaders` (and `trade_data`) |
| Pricers | `techtest/pricers` |
| RiskSystem (and `PricingConfig`) | `techtest/risk_system` (and `pricing_config`) |
| ConsoleApp | `techtest/console_app` |
| Tests | `tests` |

Class names match the C# version, including the `I...` interfaces, which are abstract base classes. Methods and
properties use Python naming, e.g. `LoadTrades()` is `load_trades()` and `TradeDate` is `trade_date`.
