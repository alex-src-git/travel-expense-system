#pragma once
#include <string>

class ReceiptConfig final
{
public:
    ReceiptConfig();
    ReceiptConfig(const std::string& currency, double pctLiableEmployeeTravel,
        double pctLiableEmployeeExpenses, double payFreeBandEmployeeTravel,
        double payFreeBandEmployeeExpenses);

    // Returns a string representing currency (e.g. Great British Pounds (GBP))
    std::string getCurrency() const;

    // Returns the percentage of the travel cost that should be played by the employee.
    double getPctLiableEmployeeTravel() const;
    
    // Returns the percentage of the expenses cost that should be played by the employee.
    double getPctLiableEmployeeExpenses() const;

    // Returns the amount of travel cost that must be reached before the employee 
    // starts paying for travel.
    double getPayFreeBandEmployeeTravel() const;

    // Returns the amount of expenses cost that must be reached before the employee 
    // starts paying expenses travel.
    double getPayFreeBandEmployeeExpenses() const;

private:
    std::string currency;
    double pctLiableEmployeeTravel;
    double pctLiableEmployeeExpenses;
    double payFreeBandEmployeeTravel;
    double payFreeBandEmployeeExpenses;
};
