#ifndef CONSOLE_MENU_BASE_H
#define CONSOLE_MENU_BASE_H

#include <string>
#include <vector>

// 菜单工具基类：提供通用的控制台输入输出辅助函数
class MenuBase
{
public:
    virtual ~MenuBase() = default;

    // 显示标题和编号选项，返回用户选择的编号（min..max）
    static int displayMenu(const std::string &title, const std::vector<std::string> &options);

    // 读取一行文本（去除首尾空白）
    static std::string readLine(const std::string &prompt);

    // 读取整数（带提示和范围校验）
    static int readInt(const std::string &prompt);

    // 按回车继续
    static void pause();

    // 清屏
    static void clearScreen();

    // 打印分隔线
    static void printSeparator(char ch = '-', int count = 60);
};

#endif // CONSOLE_MENU_BASE_H
