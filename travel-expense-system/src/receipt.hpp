#pragma once

#include "receipt-config.hpp"
#include "claim.hpp"
#include <iosfwd>
#include <ctime>
#include <string>

class Receipt final
{
public:
    Receipt(const ClaimInput& claim);
    Receipt(const ClaimInput& claim, const ReceiptConfig& receiptConfig);
    Receipt(std::size_t id, std::time_t timeCreated, ReceiptConfig cfg, 
        Money expenses, Money travel);

    std::size_t getId() const;
    std::time_t getTimeCreated() const;
    const ReceiptConfig& getConfig() const;
    std::string getTimeCreatedAsUtcString() const;
    std::string getCurrencyCode() const;

    Money getExpensesCost() const;
    Money getExpensesCostForEmployee() const;
    Money getExpensesCostForEmployer() const;

    Money getTravelCost() const;
    Money getTravelCostForEmployee() const;
    Money getTravelCostForEmployer() const;

    Money getTotalCost() const;
    Money getTotalCostForEmployee() const;
    Money getTotalCostForEmployer() const;

private:
    std::size_t getHashOfMemoryAddress(); const
    std::size_t getHashOfTimeString() const;
    std::size_t getHashOfCost() const;
    void assignId();

    // This id is constructed out of combined the hash codes of
    // 1. The instance's location in memory (i.e. (intptr)this).
    // 2. A time string.
    // 3. Cost of expenses + cost of travel.
    std::size_t id;
    std::time_t timeCreated;
    ReceiptConfig cfg;
    Money expenses;
    Money travel;
};

// This allows us to print receipt info via std::cout as if it
// was a built-in type.
std::ostream& operator << (std::ostream& os, 
    const Receipt& receipt);
