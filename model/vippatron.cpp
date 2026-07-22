#include "vippatron.h"

VIPPatron::VIPPatron(const std::string &id, const std::string &username, const std::string &phone,
                     const std::string &email, const std::string &password,
                     int borrowLimit, int vipLevel)
    : Patron(id, username, phone, email, password, borrowLimit), vipLevel(vipLevel)
{
}

// Getters
int VIPPatron::getVipLevel() const { return vipLevel; }

// Setters
void VIPPatron::setVipLevel(int level) { vipLevel = level; }

// 重写 displayInfo：先调用父类 Patron 的 displayInfo，再追加 VIP 信息
void VIPPatron::displayInfo() const {
    Patron::displayInfo();
    std::cout << "  [VIP] VIP等级: " << vipLevel << std::endl;
}

// 重写 compareTo：基于借阅上限比较两个 VIPPatron 对象
int VIPPatron::compareTo(const IComparable &other) const {
    // 尝试将 other 转换为 VIPPatron，类型不匹配则返回 -2
    const VIPPatron *otherVIP = dynamic_cast<const VIPPatron *>(&other);
    if (!otherVIP) {
        return -2;
    }

    if (getBorrowLimit() > otherVIP->getBorrowLimit()) {
        return 1;
    } else if (getBorrowLimit() == otherVIP->getBorrowLimit()) {
        return 0;
    } else {
        return -1;
    }
}
