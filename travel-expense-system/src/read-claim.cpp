#include "read-claim.hpp"
#include "ui.hpp"

static ClaimReason readClaimReason()
{
    static const std::string prompt = "Please input the reason for the claim.";
    static std::vector<std::string> options { "Travel", "Travel and Expenses" };

    auto call = std::bind(ui::switchMenu, options);
    auto index = ui::readRecursive<unsigned int>(prompt, call);

    return static_cast<ClaimReason>(index);
}

static Money readCostOfTravel()
{
    static const std::string prompt = "Please input the cost of travel.";
    return ui::readRecursive<double>(prompt, ui::readUnsignedDouble);
}

static Money readCostOfExpenses()
{
    static const std::string prompt = "Please input the cost of expenses.";
    return ui::readRecursive<double>(prompt, ui::readUnsignedDouble);
}

ClaimInput read_claim::fromUserInput()
{
    ClaimInput claim;   
    claim.reason = readClaimReason();
    claim.costOfTravel = readCostOfTravel();
    if (claim.reason == ClaimReason::TravelAndExpenses)
    {
        claim.costOfExpenses = readCostOfExpenses();
    }

    return claim;
}
