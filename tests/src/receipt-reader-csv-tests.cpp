#include <receipt.hpp>
#include <persistence/receipt-reader-csv.hpp>
#include <catch2/catch.hpp>

using namespace persistence;

static constexpr char* testFilePath = "test-file.csv";

TEST_CASE("ReceiptReaderCsvLoadWorks", "[ReceiptReaderCsv]")
{
    ReceiptReaderCsv reader;
    std::unique_ptr<Receipt> receipt = reader.load(testFilePath);
 
    REQUIRE(receipt->getId() == 0);
    REQUIRE(receipt->getTimeCreated() == 0);
    REQUIRE(receipt->getCurrencyCode() == "Pound Sterling (GBP)");
    REQUIRE(receipt->getConfig().getPctLiableEmployeeTravel() == 0.0);
    REQUIRE(receipt->getConfig().getPctLiableEmployeeExpenses() == 1.0);
    REQUIRE(receipt->getConfig().getPayFreeBandEmployeeTravel() == 0.0);
    REQUIRE(receipt->getConfig().getPayFreeBandEmployeeExpenses() == 50.0);
    REQUIRE(receipt->getExpensesCost() == 1000.0);
    REQUIRE(receipt->getTravelCost() == 200.0);
}
