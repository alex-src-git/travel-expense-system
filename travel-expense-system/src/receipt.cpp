#include "receipt.hpp"
#include <iostream>

typedef ClaimInput Claim;

static Money totalCostEmployeeExpenses(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money band = cfg.bandExpensesEmployee;
    const Money cost = claim.costOfExpenses;
    const Money multiplier = cfg.pctExpensesEmployee;
    return cost > band
        ? (cost - band) * multiplier
        : 0.0;
}

static Money totalCostEmployeeTravel(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money band = cfg.bandTravelEmployee;
    const Money cost = claim.costOfTravel;
    const Money multiplier = cfg.pctTravelEmployee;
    return cost > band
        ? (cost - band) * multiplier
        : 0.0;
}

static Money totalCostEmployerExpenses(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money total = claim.costOfExpenses;
    const Money employeeShare = totalCostEmployeeExpenses(claim, cfg);
    return total - employeeShare;
}

static Money totalCostEmployerTravel(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money total = claim.costOfTravel;
    const Money employeeShare = totalCostEmployeeTravel(claim, cfg);
    return total - employeeShare;
}

static Money totalCost(const Claim& claim, const ReceiptConfig& cfg)
{
    switch (claim.reason)
    {
        case ClaimReason::Travel:
            return claim.costOfTravel;

        case ClaimReason::TravelAndExpenses:
            return claim.costOfExpenses + claim.costOfTravel;

        default:
            std::cerr << "ClaimReason case not implemented!";
            return 0.0;
    }
}

static Money totalCostEmployee(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money travel = totalCostEmployeeTravel(claim, cfg);
    const Money expenses = totalCostEmployeeExpenses(claim, cfg);
    return travel + expenses;
}

static Money totalCostEmployer(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money total = totalCost(claim, cfg);
    const Money employeeShare = totalCostEmployee(claim, cfg);
    return total - employeeShare;
}

static Money costRebateEmployer(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money rate = cfg.rebateEmployer;
    const Money total = totalCost(claim, cfg);
    return total * rate;
}

std::unique_ptr<Receipt> 
makeReceipt(const ClaimInput& claim, const ReceiptConfig& cfg)
{
    return std::unique_ptr<Receipt>(new Receipt
    {
        .costTotal = totalCost(claim, cfg),
        .costTotalEmployer = totalCostEmployer(claim, cfg),
        .costTotalEmployee = totalCostEmployee(claim, cfg),
        .costTotalEmployeeExpenses = totalCostEmployeeExpenses(claim, cfg),
        .costTotalEmployerExpenses = totalCostEmployerExpenses(claim, cfg),
        .costTotalEmployeeTravel = totalCostEmployeeTravel(claim, cfg),
        .costTotalEmployerTravel = totalCostEmployerTravel(claim, cfg),
        .costRebateEmployer = costRebateEmployer(claim, cfg)
    });
}
