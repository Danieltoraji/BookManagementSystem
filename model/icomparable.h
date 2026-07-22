#ifndef ICOMPARABLE_H
#define ICOMPARABLE_H

// 纯抽象接口类：定义可比较对象的通用接口
// 任何继承此接口的类需实现 compareTo 方法，用于对象间的比较
class IComparable
{
public:
    virtual ~IComparable() = default;

    // 比较当前对象与另一个对象
    // 返回值：1 表示大于, 0 表示等于, -1 表示小于, -2 表示类型不匹配
    virtual int compareTo(const IComparable &other) const = 0;
};

#endif // ICOMPARABLE_H
