#pragma once

// If this was a "real" financial application, I would not use a double 
// for this - the precision is not good endough.
// I would probably either:
// 1: Import a library for handling monetary values.
// 2: Write a Money class that encapsulates integer pennies.
typedef long double Money;

enum class ClaimReason : int
{
    Travel,
    TravelAndExpenses
};

// The number of values in enum ClaimReason
constexpr int ClaimReasonValueCount = 2;

struct ClaimInput final
{
    ClaimReason reason = ClaimReason::Travel;
    Money costOfTravel = 0.0;
    Money costOfExpenses = 0.0;
};
