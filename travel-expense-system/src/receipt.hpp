#pragma once
#include "claim.hpp"
#include "receipt-config.hpp"
#include <ctime>
#include <memory>

struct Receipt final
{
    std::time_t dateTime = std::time(nullptr);
    Money costTotal = 0.0; 
    Money costTotalEmployer = 0.0;
    Money costTotalEmployee = 0.0;
    Money costEmployeeExpenses = 0.0;
    Money costEmployerExpenses = 0.0;
    Money costEmployeeTravel = 0.0;
    Money costEmployerTravel = 0.0;
    Money costRebateEmployer = 0.0;
};

std::unique_ptr<Receipt> makeReceipt(const ClaimInput& claim, const ReceiptConfig& cfg);
