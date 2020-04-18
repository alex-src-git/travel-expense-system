#pragma once

// If this was a "real" financial application, I would either use a third-party
// Money library, or a store monetary values as integers (and divide by 100).
typedef long double Money;

enum class ClaimReason : int
{
    Travel,
    TravelAndExpenses
};

// The number of values in enum: ClaimReason
constexpr int ClaimReasonValueCount = 2;

// "Plain Old Data Struct" that bundles user input values.
struct ClaimInput final
{
    ClaimReason reason = ClaimReason::Travel;
    Money costOfTravel = 0.0;
    Money costOfExpenses = 0.0;
};
