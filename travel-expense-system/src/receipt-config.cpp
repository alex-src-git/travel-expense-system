#include "receipt-config.hpp"
#include <cassert>

static constexpr char* defaultCurrency = "Pound Sterling (GBP)";
static constexpr double defaultPctLiableEmployeeTravel = 0.0;
static constexpr double defaultPctLiableEmployeeExpenses = 1.0;
static constexpr double defaultPayFreeBandEmployeeTravel = 0.0;
static constexpr double defaultPayFreeBandEmployeeExpenses = 50.0;

static bool isEmptyOrWhitespace(const std::string& string)
{
    return !(string.find_first_not_of(' ') != std::string::npos);
}

template <typename T>
static T isInsideRange(T value, T min, T max)
{
    return value >= min && value <= max;
}

ReceiptConfig::ReceiptConfig() : ReceiptConfig(defaultCurrency, 
    defaultPctLiableEmployeeTravel, defaultPctLiableEmployeeExpenses, 
    defaultPayFreeBandEmployeeTravel,
    defaultPayFreeBandEmployeeExpenses)
{
}

ReceiptConfig::ReceiptConfig(const std::string& currency,
    double pctLiableEmployeeTravel, double pctLiableEmployeeExpenses, 
    double payFreeBandEmployeeTravel, 
    double payFreeBandEmployeeExpenses) :

    currency(currency),
    pctLiableEmployeeTravel(pctLiableEmployeeTravel),
    pctLiableEmployeeExpenses(pctLiableEmployeeExpenses),
    payFreeBandEmployeeTravel(payFreeBandEmployeeTravel),
    payFreeBandEmployeeExpenses(payFreeBandEmployeeExpenses)
{
    assert(!isEmptyOrWhitespace(currency));
    assert(isInsideRange(pctLiableEmployeeExpenses, 0.0, 1.0));
    assert(isInsideRange(pctLiableEmployeeTravel, 0.0, 1.0));
    assert(payFreeBandEmployeeExpenses >= 0.0);
    assert(payFreeBandEmployeeTravel >= 0.0);
}

std::string ReceiptConfig::getCurrency() const
{
    return currency;
}

double ReceiptConfig::getPctLiableEmployeeTravel() const
{
    return pctLiableEmployeeTravel;
}

double ReceiptConfig::getPctLiableEmployeeExpenses() const
{
    return pctLiableEmployeeExpenses;
}

double ReceiptConfig::getPayFreeBandEmployeeTravel() const
{
    return payFreeBandEmployeeTravel;
}

double ReceiptConfig::getPayFreeBandEmployeeExpenses() const
{
    return payFreeBandEmployeeExpenses;
}
