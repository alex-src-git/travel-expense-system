#pragma once
#include <string>

class ReceiptConfig final
{
public:
    ReceiptConfig();
    ReceiptConfig(const std::string& currency, double pctLiableEmployeeTravel,
        double pctLiableEmployeeExpenses, double payFreeBandEmployeeTravel,
        double payFreeBandEmployeeExpenses);

    std::string getCurrency() const;
    double getPctLiableEmployeeTravel() const;
    double getPctLiableEmployeeExpenses() const;
    double getPayFreeBandEmployeeTravel() const;
    double getPayFreeBandEmployeeExpenses() const;

private:

    std::string currency;
    double pctLiableEmployeeTravel;
    double pctLiableEmployeeExpenses;
    double payFreeBandEmployeeTravel;
    double payFreeBandEmployeeExpenses;
};
