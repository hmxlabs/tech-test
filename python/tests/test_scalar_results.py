import unittest

from techtest.models import ScalarResults

DUMMY_TRADE_ID_ONE = "TradeOne"
DUMMY_RESULT_ONE = 100.00
DUMMY_ERROR_ONE = "ErrorMessageOne"

DUMMY_TRADE_ID_TWO = "TradeTwo"
DUMMY_RESULT_TWO = 50.525
DUMMY_ERROR_TWO = "ErrorMessageTwo;"

DUMMY_TRADE_ID_THREE = "TradeThree"
DUMMY_RESULT_THREE = 12.5

DUMMY_TRADE_ID_FOUR = "TradeFour"
DUMMY_ERROR_FOUR = "ErrorMessageFour"


class ScalarResultsTests(unittest.TestCase):
    def test_result_insertion(self):
        results = ScalarResults()
        results.add_result(DUMMY_TRADE_ID_ONE, DUMMY_RESULT_ONE)

        result = results[DUMMY_TRADE_ID_ONE]
        self.assertEqual(result.trade_id, DUMMY_TRADE_ID_ONE)
        self.assertEqual(result.result, DUMMY_RESULT_ONE)

    def test_error_insertion(self):
        results = ScalarResults()
        results.add_error(DUMMY_TRADE_ID_ONE, DUMMY_ERROR_ONE)

        result = results[DUMMY_TRADE_ID_ONE]
        self.assertEqual(result.trade_id, DUMMY_TRADE_ID_ONE)
        self.assertEqual(result.error, DUMMY_ERROR_ONE)

    def test_combined_error_and_result_insertion(self):
        results = ScalarResults()
        results.add_result(DUMMY_TRADE_ID_ONE, DUMMY_RESULT_ONE)
        results.add_error(DUMMY_TRADE_ID_ONE, DUMMY_ERROR_ONE)

        result = results[DUMMY_TRADE_ID_ONE]
        self.assertEqual(result.trade_id, DUMMY_TRADE_ID_ONE)
        self.assertEqual(result.error, DUMMY_ERROR_ONE)
        self.assertEqual(result.result, DUMMY_RESULT_ONE)

    def test_contains_positive(self):
        results = ScalarResults()
        results.add_error(DUMMY_TRADE_ID_ONE, DUMMY_ERROR_ONE)
        self.assertTrue(results.contains_trade(DUMMY_TRADE_ID_ONE))

        results = ScalarResults()
        results.add_result(DUMMY_TRADE_ID_ONE, DUMMY_RESULT_ONE)
        self.assertTrue(results.contains_trade(DUMMY_TRADE_ID_ONE))

    def test_contains_negative(self):
        results = ScalarResults()
        results.add_error(DUMMY_TRADE_ID_ONE, DUMMY_ERROR_ONE)
        self.assertFalse(results.contains_trade(DUMMY_TRADE_ID_TWO))

        results = ScalarResults()
        results.add_result(DUMMY_TRADE_ID_ONE, DUMMY_RESULT_TWO)
        self.assertFalse(results.contains_trade(DUMMY_TRADE_ID_TWO))

    def test_enumeration(self):
        results = ScalarResults()
        results.add_result(DUMMY_TRADE_ID_ONE, DUMMY_RESULT_ONE)
        results.add_error(DUMMY_TRADE_ID_ONE, DUMMY_ERROR_ONE)
        results.add_result(DUMMY_TRADE_ID_TWO, DUMMY_RESULT_TWO)
        results.add_error(DUMMY_TRADE_ID_TWO, DUMMY_ERROR_TWO)
        results.add_result(DUMMY_TRADE_ID_THREE, DUMMY_RESULT_THREE)
        results.add_error(DUMMY_TRADE_ID_FOUR, DUMMY_ERROR_FOUR)

        results_list = list(results)
        self.assertEqual(len(results_list), 4)

        dummy_result = next(res for res in results_list if res.trade_id == DUMMY_TRADE_ID_ONE)
        self.assertIsNotNone(dummy_result)
        self.assertEqual(dummy_result.result, DUMMY_RESULT_ONE)
        self.assertEqual(dummy_result.error, DUMMY_ERROR_ONE)

        dummy_result = next(res for res in results_list if res.trade_id == DUMMY_TRADE_ID_TWO)
        self.assertIsNotNone(dummy_result)
        self.assertEqual(dummy_result.result, DUMMY_RESULT_TWO)
        self.assertEqual(dummy_result.error, DUMMY_ERROR_TWO)

        dummy_result = next(res for res in results_list if res.trade_id == DUMMY_TRADE_ID_THREE)
        self.assertIsNotNone(dummy_result)
        self.assertEqual(dummy_result.result, DUMMY_RESULT_THREE)
        self.assertIsNone(dummy_result.error)

        dummy_result = next(res for res in results_list if res.trade_id == DUMMY_TRADE_ID_FOUR)
        self.assertIsNotNone(dummy_result)
        self.assertIsNone(dummy_result.result)
        self.assertEqual(dummy_result.error, DUMMY_ERROR_FOUR)


if __name__ == "__main__":
    unittest.main()
