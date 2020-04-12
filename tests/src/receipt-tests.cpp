#include <receipt.hpp>
#include <catch2/catch.hpp>

TEST_CASE("makeReceiptCorrectlyCalculatesReceiptValuesWithSpecificationConfig", "[Receipt]")
{
    ClaimInput claim = ClaimInput
    {
        .reason = ClaimReason::TravelAndExpenses,
        .costOfTravel = 1000.0,
        .costOfExpenses = 200.0
    };

    ReceiptConfig cfg = ReceiptConfig
    {
        .pctTravelEmployee = 0.0,
        .pctExpensesEmployee = 1.0,
        .bandTravelEmployee = 0.0,
        .bandExpensesEmployee = 50.0
    };

    Receipt receipt = Receipt(claim, cfg);

    REQUIRE(receipt.getTotalCost() == 1200.0);
    REQUIRE(receipt.getTotalCostForEmployer() == 1050);
    REQUIRE(receipt.getTotalCostForEmployee() == 150);

    REQUIRE(receipt.getExpensesCost() == 200);
    REQUIRE(receipt.getExpensesCostForEmployee() == 150);
    REQUIRE(receipt.getExpensesCostForEmployer() == 50);

    REQUIRE(receipt.getTravelCostForEmployee() == 0);
    REQUIRE(receipt.getTravelCostForEmployer() == 1000);
    REQUIRE(receipt.getTravelCost() == 1000);
}

TEST_CASE("makeReceiptCorrectlyCalculatesReceiptValuesWithComplexConfig", "[Receipt]")
{
    ClaimInput claim = ClaimInput
    {
        .reason = ClaimReason::TravelAndExpenses,
        .costOfTravel = 1000.0,
        .costOfExpenses = 200.0
    };

    ReceiptConfig cfg = ReceiptConfig
    {
        .pctTravelEmployee = 0.5,
        .pctExpensesEmployee = 1.0,
        .bandTravelEmployee = 200,
        .bandExpensesEmployee = 50.0
    };

    Receipt receipt = Receipt(claim, cfg);

    REQUIRE(receipt.getTotalCost() == 1200.0);
    REQUIRE(receipt.getTotalCostForEmployer() == 650);
    REQUIRE(receipt.getTotalCostForEmployee() == 550);

    REQUIRE(receipt.getExpensesCost() == 200);
    REQUIRE(receipt.getExpensesCostForEmployee() == 150);
    REQUIRE(receipt.getExpensesCostForEmployer() == 50);

    REQUIRE(receipt.getTravelCostForEmployee() == 400);
    REQUIRE(receipt.getTravelCostForEmployer() == 600);
    REQUIRE(receipt.getTravelCost() == 1000);
}
