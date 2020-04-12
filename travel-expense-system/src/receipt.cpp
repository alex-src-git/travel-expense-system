#include "receipt.hpp"
#include <iostream>

Receipt::Receipt(const ClaimInput& claim) : Receipt(claim, {})
{
}

Receipt::Receipt(const ClaimInput & claim, const ReceiptConfig & receiptConfig) :
    timeCreated(time(nullptr)),
    cfg(receiptConfig),
    expenses(claim.costOfExpenses),
    travel(claim.costOfTravel)
{
}

std::time_t Receipt::getTimeCreated() const
{
    return timeCreated;
}

std::string Receipt::getTimeCreatedAsUtcString() const
{
    #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
    tm* time = std::gmtime(&timeCreated);
    char* timeAsCString = std::asctime(time);
    return std::string(timeAsCString);
    #pragma warning(default : 4996)
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

// TODO: Print as a table.
std::ostream& operator << (std::ostream& os, const Receipt& receipt)
{
    os << "\nCreated  : " << receipt.getTimeCreatedAsUtcString();

    os << "\nTotal    : " << receipt.getTotalCost();
    os << "\nEmployee : " << receipt.getTotalCostForEmployee();
    os << "\nEmployer : " << receipt.getTotalCostForEmployer();

    os << "\n\nExpenses : " << receipt.getExpensesCost();
    os << "\nEmployee : " << receipt.getExpensesCostForEmployee();
    os << "\nEmployer : " << receipt.getExpensesCostForEmployer();

    os << "\n\nTravel   : " << receipt.getTravelCost();
    os << "\nEmployee : " << receipt.getTravelCostForEmployee();
    os << "\nEmployer : " << receipt.getTravelCostForEmployer();

    return os;
}
