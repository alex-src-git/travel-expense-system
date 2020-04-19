#include "receipt-queries.hpp"

Receipt* receipt_queries::getLargestPayment(const ReceiptVector& receipts)
{
    Money largestCost = 0;
    std::size_t indexOfLargest = 0;

    for (std::size_t i = 0; i < receipts.size(); i++)
    {
        // FIXME: What if multiple receipts have the same total cost?
        const Money cost = receipts[i]->getTotalCost();
        if (cost > largestCost)
        {
            largestCost = cost;
            indexOfLargest = i;
        }
    }

    return receipts[indexOfLargest].get();
}

Money receipt_queries::getAverageCostOfTravel(const ReceiptVector& receipts)
{
    Money average = 0;
    for (const auto& receipt : receipts)
    {
        average += receipt->getTravelCost();
    }

    return average;
}

Money receipt_queries::getAverageCostOfExpenses(const ReceiptVector& receipts)
{
    Money average = 0;
    for (const auto& receipt : receipts)
    {
        average += receipt->getExpensesCost();
    }

    return average;
}
