#pragma once

struct ReceiptConfig final
{
    double pctTravelEmployer = 100;
    double pctExpensesEmployer = 0;
    double bandTravelEmployee = 0;
    double bandExpensesEmployee = 50;
    char currency[4] = "GBP";
};
