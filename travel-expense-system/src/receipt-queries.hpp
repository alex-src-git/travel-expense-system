#pragma once
#include "receipt.hpp"
#include <vector>
#include <memory>

namespace receipt_queries
{
    typedef std::vector<std::unique_ptr<Receipt>> ReceiptVector;

    Receipt* getLargestPayment(const ReceiptVector& receipts);
    Money getAverageCostOfTravel(const ReceiptVector& receipts);
    Money getAverageCostOfExpenses(const ReceiptVector& receipts);
}
