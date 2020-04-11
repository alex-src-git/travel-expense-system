#pragma once

struct ReceiptConfig final
{
    // The percentage of the total travel cost to be payed by the employer.
    double pctTravelEmployer = 100;

    // The percentage of the expenses cost to be payed by the employer.
    double pctExpensesEmployer = 0;

    // The minimum amount of money spent on travel before the employee has to pay.
    double bandTravelEmployee = 0;

    // The minimum amount of money spent on expenses before the employee has to pay.
    double bandExpensesEmployee = 50;

    // The currency name (i.e. GBP).
    // Array length of 4 to account for the termination character.
    char currency[4] = "GBP";
};
