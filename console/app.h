#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include <string>

// 主应用控制器：管理登录流程和角色菜单分发
class App
{
public:
    // 启动应用主循环
    void run();

private:
    // 登录流程，返回 true 表示成功登录，false 表示退出
    bool loginFlow();

    // 显示登录菜单
    int showLoginMenu();

    // 登录操作
    bool doLogin();

    // 注册操作（调用 userService 添加新用户）
    void doRegister();
};

#endif // CONSOLE_APP_H
