#pragma once

struct ReceiptConfig final
{
    double pctTravelEmployee = 1.0;
    double pctExpensesEmployee = 0;
    double bandTravelEmployee = 0;
    double bandExpensesEmployee = 50;
    double rebateEmployer = 0.2;
    char currency[4] = "GBP";
};
