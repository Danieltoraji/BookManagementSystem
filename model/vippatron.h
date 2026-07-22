#ifndef VIPPATRON_H
#define VIPPATRON_H

#include "patron.h"
#include "icomparable.h"
#include <iostream>

// VIP读者类：多重继承自 Patron 和 IComparable
// - 继承 Patron：拥有普通读者的全部属性和行为（借阅上限等）
// - 继承 IComparable：实现 compareTo 方法，支持基于借阅上限的对象比较
class VIPPatron : public Patron, public IComparable
{
private:
    int vipLevel; // VIP等级（1-5）

public:
    VIPPatron(const std::string &id, const std::string &username, const std::string &phone,
              const std::string &email, const std::string &password,
              int borrowLimit = 10, int vipLevel = 1);

    // Getters
    int getVipLevel() const;

    // Setters
    void setVipLevel(int level);

    // 重写 User 的纯虚函数
    void displayInfo() const override;

    // 重写 IComparable 的纯虚函数
    // 基于 borrowLimit 比较：1=大于, 0=等于, -1=小于, -2=类型不匹配
    int compareTo(const IComparable &other) const override;
};

#endif // VIPPATRON_H
