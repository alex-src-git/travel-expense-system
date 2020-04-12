#pragma once
#include "receipt-config.hpp"
#include "claim.hpp"
#include <iosfwd>

class Receipt final
{
public:
    Receipt(const ClaimInput& claim);
    Receipt(const ClaimInput& claim, const ReceiptConfig& receiptConfig);

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
    ReceiptConfig cfg;
    Money expenses;
    Money travel;
};

std::ostream& operator << (std::ostream& os, 
    const Receipt& receipt);
