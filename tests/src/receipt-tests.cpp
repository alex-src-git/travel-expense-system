#include <receipt.hpp>
#include <catch2/catch.hpp>
#include <thread>

TEST_CASE("makeReceiptCorrectlyCalculatesReceiptValuesWithSpecificationConfig", "[Receipt]")
{
    ClaimInput claim = ClaimInput
    {
        .reason = ClaimReason::TravelAndExpenses,
        .costOfTravel = 1000.0,
        .costOfExpenses = 200.0
    };

    ReceiptConfig cfg = ReceiptConfig("Pound Sterling (GPB)", 0.0, 1.0, 0.0, 50.0);
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

    ReceiptConfig cfg = ReceiptConfig("Pound Sterling (GPB)", 0.5, 1.0, 200.0, 50.0);
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

TEST_CASE("makeReceiptAssignsAnAcceptablyUniqueID", "[Receipt]")
{
    Receipt lhs = Receipt({});
    Receipt rhs = Receipt({});
    
    REQUIRE(lhs.getId() != rhs.getId());
}
