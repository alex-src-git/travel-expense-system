#include "ui.hpp"
#include "read-claim.hpp"
#include "receipt.hpp"
#include "receipt-queries.hpp"
#include "persistence/receipt-writer-csv.hpp"
#include "persistence/receipt-reader-csv.hpp"

typedef std::vector<std::unique_ptr<Receipt>> ReceiptVector;

static void saveReceipt(const Receipt& receipt)
{
    persistence::ReceiptWriterCsv writer;
    writer.save(receipt);
}

static void addNewClaim()
{
    ClaimInput claim = read_claim::fromUserInput();
    Receipt receipt = Receipt(claim);
    ui::writeLine(receipt);
    
    if (ui::readRecursive<bool>("Would you like to save this receipt? (y/n)", ui::readBool))
    {
        saveReceipt(receipt);
    }
}

static void writeReceiptCount(const ReceiptVector& receipts)
{
    std::size_t numReceipts = receipts.size();
    if (numReceipts == 0)
    {
        ui::writeError("No receipts found.");
    }
    else
    {
        ui::writeHeading(std::to_string(numReceipts) + "x Receipts found.");
    }
}

static void writeLargestPayments(const Receipt& receipt)
{
    ui::writeHeading("Largest payment");
    ui::writeLine(receipt);
}

static void writeAveragePayments(Money averageTravel, Money averageExpenses)
{
    ui::writeHeading("Averages payments");
    ui::writeLine("Travel   : " + std::to_string(averageTravel));
    ui::writeLine("Expenses : " + std::to_string(averageExpenses));
    ui::writeLine("Total    : " + std::to_string(averageTravel + averageExpenses));
}

static void quit()
{
    ui::writeHeading("Goodbye");
}

static void queryReceiptsMenu()
{
    persistence::ReceiptReaderCsv reader;
    auto receipts = reader.loadAll();
    
    writeReceiptCount(receipts);
    
    if (receipts.size() == 0)
    {
        return;
    }

    static const std::vector<std::string> options{ "Print largest payment", "Print average payments", "Quit to main menu" };
    auto optionSelector = std::bind(ui::switchMenu, options);

    while (true)
    {
        switch (ui::readRecursive<unsigned int>("Query Receipts", optionSelector))
        {
            case 0:
            {
                // We don't need to `delete` this pointer because its lifetime is managed by `std::unique_ptr`.
                Receipt* largestPayment = receipt_queries::getLargestPayment(receipts);
                writeLargestPayments(*largestPayment);
                break;
            }
            case 1:
            {
                Money averageTravel = receipt_queries::getAverageCostOfTravel(receipts);
                Money averageExpenses = receipt_queries::getAverageCostOfExpenses(receipts);
                writeAveragePayments(averageTravel, averageExpenses);
                break;
            }
            case 2:
            {
                return;
            }
        }
    }
}

static void mainMenu(bool& isRunning)
{
    static const std::vector<std::string> options{ "Add a new claim", "Query Receipts", "Quit" };
    auto optionSelector = std::bind(ui::switchMenu, options);
    
    switch (ui::readRecursive<unsigned int>("Travel Expense System", optionSelector))
    {
        case 0:
        {
            addNewClaim();
            break;
        }
        case 1:
        {
            queryReceiptsMenu();
            break;
        }
        case 2:
        {
            quit();
            isRunning = false;
            break;
        }
    }
}

int main()
{
    bool isRunning = true;
    while (isRunning)
    {
        mainMenu(isRunning);
    }

    return 0;
}
