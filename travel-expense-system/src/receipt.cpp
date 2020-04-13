#include "receipt.hpp"
#include <iostream>
#include <algorithm>

Receipt::Receipt(const ClaimInput& claim) : Receipt(claim, {})
{
}

Receipt::Receipt(const ClaimInput & claim, const ReceiptConfig & receiptConfig) :
    timeCreated(time(nullptr)),
    cfg(receiptConfig),
    expenses(claim.costOfExpenses),
    travel(claim.costOfTravel)
{
    assignId();
}

std::size_t Receipt::getId() const
{
    return id;
}

std::time_t Receipt::getTimeCreated() const
{
    return timeCreated;
}

std::string Receipt::getTimeCreatedAsUtcString() const
{
    #pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

    tm* time = std::gmtime(&timeCreated);
    std::string str(std::asctime(time));
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    str += " (UTC)";
    return str;

    #pragma warning(default : 4996)
}

std::string Receipt::getCurrencyCode() const
{
    return std::string(cfg.currency);
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

std::size_t Receipt::getHashOfMemoryAddress()
{
    auto uintPtr = (std::uintptr_t)std::addressof(*this);
    return std::hash<std::uintptr_t>{}(uintPtr);
}

const std::size_t Receipt::getHashOfTimeString() const
{
    std::string timeString = getTimeCreatedAsUtcString();
    return std::hash<std::string>{}(timeString);
}

std::size_t Receipt::getHashOfCost() const
{
    Money total = expenses + travel;
    return std::hash<Money>{}(total);
}

void Receipt::assignId()
{
    id = getHashOfMemoryAddress() ^ getHashOfTimeString() ^ getHashOfCost();
}

// TODO: Print as a table.
std::ostream& operator << (std::ostream& os, const Receipt& receipt)
{
    os << "\nID Hash  : " << std::hex << receipt.getId();
    os << "\nCreated  : " << receipt.getTimeCreatedAsUtcString();
    os << "\nCurrency : " << receipt.getCurrencyCode();

    os << "\n\nExpenses : " << receipt.getExpensesCost();
    os << "\nEmployee : " << receipt.getExpensesCostForEmployee();
    os << "\nEmployer : " << receipt.getExpensesCostForEmployer();

    os << "\n\nTravel   : " << receipt.getTravelCost();
    os << "\nEmployee : " << receipt.getTravelCostForEmployee();
    os << "\nEmployer : " << receipt.getTravelCostForEmployer();

    os << "\n\nTotal    : " << receipt.getTotalCost();
    os << "\nEmployee : " << receipt.getTotalCostForEmployee();
    os << "\nEmployer : " << receipt.getTotalCostForEmployer();

    return os;
}
