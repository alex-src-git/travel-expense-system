#pragma once
#include "claim.hpp"
#include <ctime>

struct Receipt final
{
    std::time_t dateTime = std::time(nullptr);
    Money costTotal = 0.0; 
    Money costTotalEmployer = 0.0;
    Money costTotalEmployee = 0.0;
    Money costTotalEmployeeExpenses = 0.0;
    Money costTotalEmployerExpenses = 0.0;
    Money costTotalEmployeeTravel = 0.0;
    Money costTotalEmployerTravel = 0.0;
    Money costRebateEmployer = 0.0;
};
