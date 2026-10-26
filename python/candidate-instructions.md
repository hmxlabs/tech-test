# Introduction

This test is an extremely simplified and rather contrived example of what a risk system in a typical bank might look like. For the purposes of simplicity of this test, market and static data as well presentation (UI & UX) have been completely ignored.

For the purposes of this test, imagine that this is a new system that was originally developed only to handle government bonds and is now being extended to handle corporate bonds and FX. As a result the system needs to be enhanced.

All of the below exercises should be performed as though you are working on a real risk system. **You should feel free to refactor any code as you see fit and you should always attempt to reuse as much code and possible and write the minimum amount of new code.**

Apart from the exercises where you are asked to write or modify unit tests, none of the other unit tests should be modified.

There are a number of occasions in the test where multiple solutions are possible. You should decide how it is most appropriate to proceed and be prepared to justify your decisions and assumptions.

At the end of the exercise all of the code should run, the unit tests should run successfully and the program should produce the expected output.

# Rules

This test should take about 2 hours to complete and you should try and limit your time to this. You should allocate your time accordingly and skip any questions you are unable to complete. The questions get progressively more difficult, the first few questions should take only a matter of minutes to complete, the later questions will take longer. Depending on your experience you may not be able to complete all of the questions. This is deliberate and expected.

You may use any resources you wish to complete the test. You may use the internet, books, or any other resources you have available including AI tools. You should not ask for help from any other person. **You will be asked to explain your solution and justify your decisions.**

You should not use any third party libraries or introduce any new dependencies in order to complete the test. You may use any functionality you wish that is provided by the Python standard library.

See the [README](./README.md) for how to run the tests and the application. Start by forking this repository to your own GitHub account. You should commit your code after each exercise at a minimum. Once you have completed the test, please send the URL of your repository to your interviewer.

# Exercises

## Exercise 1
Modify the [BondTradeLoader](./techtest/loaders/bond_trade_loader.py) class to correctly process the bond feed file ([BondTrades.dat](./techtest/loaders/trade_data/BondTrades.dat)) such that it now creates the correct objects for both government and corporate bonds. Once this is complete the BondTradeLoaderTests should all pass.

## Exercise 2
Implement the [FxTradeLoader](./techtest/loaders/fx_trade_loader.py) class so that it can read the FX trades feed file([FxTrades.dat](./techtest/loaders/trade_data/FxTrades.dat)). The Instrument field should be constructed as the concatenation of Ccy1 and Ccy2. Once this is implemented the FxTradeLoaderTests should all pass

## Exercise 3
Implement the [PricingConfigLoader](./techtest/risk_system/pricing_config_loader.py) class such that it loads the contents of the [PricingEngines.xml](./techtest/risk_system/pricing_config/PricingEngines.xml) file and provides an enumeration of PricingEngineConfigItem objects. Once this is implemented the PricingConfigLoaderTests should all pass.

## Exercise 4
Implement the `_load_pricers` method in the [SerialPricer](./techtest/risk_system/serial_pricer.py) class so that it instantiates each of the required types of pricing engines dynamically. There should be no import-time dependency between the `risk_system` and `pricers` packages.

## Exercise 5
Complete the implementation of the [ScalarResults](./techtest/models/scalar_results.py) class such that it fully supports iteration (`__iter__`), producing one `ScalarResult` per trade. Once this is complete the ScalarResultsTests should all pass.

## Exercise 6
Implement the [ScreenResultPrinter](./techtest/risk_system/screen_result_printer.py) class. It should output one line to the screen for each trade in the following formats:

If there is both a result and an error : “TradeID : Result : Error”
If there is a result but no error: “TradeID : Result”
If there is an error but no result: “TradeID : Error”
At this point you should be able to run the application (`python -m techtest.console_app`). It should load all of the trades and print one line per trade with results output.

## Exercise 7
The risk system in its state as provided loads all of the trades from all trade sources before attempting to start to price any of them. For a high volume system this could present serious memory problems. Change the implementation of the trade loaders and the system such that it will load a trade and immediately send it to be priced so that the entire trade population does not have to be held in memory. It is acceptable to have all of the results still held in memory for the purposes of this test.