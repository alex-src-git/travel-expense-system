#pragma once
#include <string>

struct ReceiptConfig final
{
    double pctTravelEmployee = 0;
    double pctExpensesEmployee = 1;
    double bandTravelEmployee = 0;
    double bandExpensesEmployee = 50;
    std::string currency = "Pound Sterling (UK)";
};
