#include "timeservice.h"

TimeService::TimeService()
{
}

TimeService& TimeService::getInstance()
{
    static TimeService instance;
    return instance;
}

Date TimeService::calculateDueDate(const Date& loanDate) const
{
    return loanDate + DEFAULT_BORROW_DAYS;
}

Date TimeService::calculateRenewedDueDate(const Date& currentDueDate) const
{
    return currentDueDate + RENEW_DAYS;
}
