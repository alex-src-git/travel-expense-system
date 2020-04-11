#pragma once

typedef long double Money;

enum class ClaimReason : int
{
    Travel,
    TravelAndExpenses
};
constexpr int ClaimReasonValueCount = 2;

struct ClaimInput final
{
    ClaimReason reason = ClaimReason::Travel;
    Money costOfTravel = 0.0;
    Money costOfExpenses = 0.0;
};
