#include <receipt.hpp>
#include <catch2/catch.hpp>
#include <memory>

TEST_CASE("makeReceiptCorrectlyCalculatesReceiptValuesWithSpecificationConfig", "[Receipt]")
{
    auto claim = std::unique_ptr<ClaimInput>(new ClaimInput
    {
        .reason = ClaimReason::TravelAndExpenses,
        .costOfTravel = 1000.0,
        .costOfExpenses = 200.0
    });

    auto cfg = std::unique_ptr<ReceiptConfig>(new ReceiptConfig
    {
        .pctTravelEmployee = 0.0,
        .pctExpensesEmployee = 1.0,
        .bandTravelEmployee = 0.0,
        .bandExpensesEmployee = 50.0,
        .rebateEmployer = 0.2
    });

    std::unique_ptr<Receipt> receipt = makeReceipt(*claim, *cfg);

    REQUIRE(receipt->costTotal == 1200.0);
    REQUIRE(receipt->costTotalEmployer == 1050);
    REQUIRE(receipt->costTotalEmployee == 150);
    REQUIRE(receipt->costEmployeeExpenses == 150);
    REQUIRE(receipt->costEmployerExpenses == 50);
    REQUIRE(receipt->costTotalExpenses == 200);
    REQUIRE(receipt->costEmployeeTravel == 0);
    REQUIRE(receipt->costEmployerTravel == 1000);
    REQUIRE(receipt->costTotalTravel == 1000);
    REQUIRE(receipt->costRebateEmployer == 240);
}

TEST_CASE("makeReceiptCorrectlyCalculatesReceiptValuesWithComplexConfig", "[Receipt]")
{
    auto claim = std::unique_ptr<ClaimInput>(new ClaimInput
    {
        .reason = ClaimReason::TravelAndExpenses,
        .costOfTravel = 1000.0,
        .costOfExpenses = 200.0
    });

    auto cfg = std::unique_ptr<ReceiptConfig>(new ReceiptConfig
    {
        .pctTravelEmployee = 0.5,
        .pctExpensesEmployee = 1.0,
        .bandTravelEmployee = 200,
        .bandExpensesEmployee = 50.0,
        .rebateEmployer = 0.2
    });

    std::unique_ptr<Receipt> receipt = makeReceipt(*claim, *cfg);

    REQUIRE(receipt->costTotal == 1200.0);
    REQUIRE(receipt->costTotalEmployer == 650);
    REQUIRE(receipt->costTotalEmployee == 550);
    REQUIRE(receipt->costEmployeeExpenses == 150);
    REQUIRE(receipt->costEmployerExpenses == 50);
    REQUIRE(receipt->costTotalExpenses == 200);
    REQUIRE(receipt->costEmployeeTravel == 400);
    REQUIRE(receipt->costEmployerTravel == 600);
    REQUIRE(receipt->costTotalTravel == 1000);
    REQUIRE(receipt->costRebateEmployer == 240);
}
