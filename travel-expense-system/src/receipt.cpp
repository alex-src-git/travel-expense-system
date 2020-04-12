#include "receipt.hpp"
#include <iostream>
#include <sstream>

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

static Money totalCostExpenses(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money employee = totalCostEmployeeExpenses(claim, cfg);
    const Money employer = totalCostEmployerExpenses(claim, cfg);
    return employee + employer;
}

static Money totalCostTravel(const Claim& claim, const ReceiptConfig& cfg)
{
    const Money employee = totalCostEmployeeTravel(claim, cfg);
    const Money employer = totalCostEmployerTravel(claim, cfg);
    return employee + employer;
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
        .costEmployeeExpenses = totalCostEmployeeExpenses(claim, cfg),
        .costEmployerExpenses = totalCostEmployerExpenses(claim, cfg),
        .costTotalExpenses = totalCostExpenses(claim, cfg),
        .costEmployeeTravel = totalCostEmployeeTravel(claim, cfg),
        .costEmployerTravel = totalCostEmployerTravel(claim, cfg),
        .costTotalTravel = totalCostTravel(claim, cfg),
        .costRebateEmployer = costRebateEmployer(claim, cfg)
    });
}

std::string stringifyReceipt(const Receipt& receipt)
{
    std::stringstream ss;

    ss << std::endl << "Expenses" << std::endl;
    ss << "Employee : " << receipt.costEmployeeExpenses << std::endl;
    ss << "Employer : " << receipt.costEmployerExpenses << std::endl;
    ss << "Total    : " << receipt.costTotalExpenses << std::endl;
    
    ss << std::endl << "Travel" << std::endl;
    ss << "Employee : " << receipt.costEmployeeTravel << std::endl;
    ss << "Employer : " << receipt.costEmployerTravel << std::endl;
    ss << "Total    : " << receipt.costTotalTravel << std::endl;

    ss << std::endl << "Total" << std::endl;
    ss << "Employee : " << receipt.costTotalEmployee << std::endl;
    ss << "Employer : " << receipt.costTotalEmployer << std::endl;
    ss << "Total    : " << receipt.costTotal << std::endl;
    
    return ss.str();
}
