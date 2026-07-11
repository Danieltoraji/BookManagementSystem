#ifndef TIMESERVICE_H
#define TIMESERVICE_H
#include "model/date.h"

class TimeService
{
public:
    // 单例实现
    static TimeService& getInstance();
    TimeService(const TimeService&) = delete;
    TimeService& operator=(const TimeService&) = delete;
    TimeService(TimeService&&) = delete;
    TimeService& operator=(TimeService&&) = delete;

    // 借阅规则常量
    static constexpr int DEFAULT_BORROW_DAYS = 30; // 默认借阅期 30 天
    static constexpr int RENEW_DAYS = 15;           // 续期 15 天

    // 业务日期计算（结合借阅规则常量，纯日期运算由 Date 运算符完成）
    Date calculateDueDate(const Date& loanDate) const;            // 计算应还日期 = 借书日期 + 30天
    Date calculateRenewedDueDate(const Date& currentDueDate) const; // 续期后应还日期 = 当前应还日期 + 15天

private:
    TimeService();
};

#endif // TIMESERVICE_H
