#include "ui.hpp"
#include "read-claim.hpp"
#include "receipt.hpp"

static void addNewClaim()
{
    ClaimInput claim = read_claim::fromUserInput();
    Receipt receipt = Receipt(claim);
    ui::writeLine(receipt);
}

static void quit()
{
    ui::writeLine("Goodbye");
}

static void mainMenu(bool& isRunning)
{
    static const std::vector<std::string> options{ "Add a new claim", "Quit" };
    auto optionSelector = std::bind(ui::switchMenu, options);
    
    switch (ui::readRecursive<unsigned int>("Travel Expense System", optionSelector))
    {
        case 0:
            addNewClaim();
            break;

        case 1:
            quit();
            isRunning = false;
            break;
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
