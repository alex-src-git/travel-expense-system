#include "receipt.hpp"
#include <iostream>

Receipt::Receipt(const ClaimInput& claim) : Receipt(claim, {})
{
}

Receipt::Receipt(const ClaimInput& claim, const ReceiptConfig& receiptConfig) : 
    cfg(receiptConfig),
    expenses(claim.costOfExpenses),
    travel(claim.costOfTravel)
{
}

Money Receipt::getExpensesCost() const
{
    return expenses;
}

Money Receipt::getExpensesCostForEmployee() const
{
    return expenses > cfg.bandExpensesEmployee
        ? (expenses - cfg.bandExpensesEmployee) * cfg.pctExpensesEmployee
        : 0.0;
}

Money Receipt::getExpensesCostForEmployer() const
{
    return expenses - getExpensesCostForEmployee();
}

Money Receipt::getTravelCost() const
{
    return travel;
}

Money Receipt::getTravelCostForEmployee() const
{
    return travel > cfg.bandTravelEmployee
        ? (travel - cfg.bandTravelEmployee) * cfg.pctTravelEmployee
        : 0.0;
}

Money Receipt::getTravelCostForEmployer() const
{
    return travel - getTravelCostForEmployee();
}

Money Receipt::getTotalCost() const
{
    return travel + expenses;
}

Money Receipt::getTotalCostForEmployee() const
{
    return getTravelCostForEmployee() + getExpensesCostForEmployee();
}

Money Receipt::getTotalCostForEmployer() const
{
    return getTravelCostForEmployer() + getExpensesCostForEmployer();
}

std::ostream& operator << (std::ostream& os, const Receipt& receipt)
{
    os << std::endl << "Total    : " << receipt.getTotalCost() << std::endl;
    os << "Employee : " << receipt.getTotalCostForEmployee() << std::endl;
    os << "Employer : " << receipt.getTotalCostForEmployer() << std::endl;

    os << std::endl << "Expenses : " << receipt.getExpensesCost() << std::endl;
    os << "Employee : " << receipt.getExpensesCostForEmployee() << std::endl;
    os << "Employer : " << receipt.getExpensesCostForEmployer() << std::endl;    

    os << std::endl << "Travel   : " << receipt.getTravelCost() << std::endl;
    os << "Employee : " << receipt.getTravelCostForEmployee() << std::endl;
    os << "Employer : " << receipt.getTravelCostForEmployer() << std::endl;

    return os;
}
