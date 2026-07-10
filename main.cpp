#include "console/app.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    // 设置控制台为 UTF-8 编码，解决中文乱码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    App app;
    app.run();
    return 0;
}
