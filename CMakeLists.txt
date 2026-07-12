cmake_minimum_required(VERSION 3.15)

project(BookManagementSystem VERSION 1.0.0 LANGUAGES CXX)

# C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出目录统一到 build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 源文件列表
set(SOURCES
    main.cpp
    console/app.cpp
    console/menu_base.cpp
    console/admin_menu.cpp
    console/user_menu.cpp
    model/book.cpp
    model/bookcopy.cpp
    model/user.cpp
    model/admin.cpp
    model/patron.cpp
    model/loan.cpp
    model/date.cpp
    model/location.cpp
    services/bookservice.cpp
    services/bookcopyservice.cpp
    services/loanservice.cpp
    services/timeservice.cpp
    services/userservice.cpp
    dao/bookdao.cpp
    dao/bookcopydao.cpp
    dao/loandao.cpp
    dao/userdao.cpp
)

# 可执行目标
add_executable(BookManagementSystem ${SOURCES}
    console/user_submenu/search_info_menu.cpp
    console/user_submenu/loan_menu.cpp
    console/user_submenu/personal_info_menu.cpp)

# 包含目录
target_include_directories(BookManagementSystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# MSVC 编译选项：UTF-8 编码、精确头文件依赖追踪、加速增量构建
if(MSVC)
    target_compile_options(BookManagementSystem PRIVATE
        /utf-8
        /W3
        /sourceDependencies  # 输出 JSON 格式的源文件依赖信息，CMake 4.4 据此做精确增量构建
        /Zf                  # 并行 PDB 生成，加速增量构建
    )
endif()

# Debug/Release 配置
set(CMAKE_DEBUG_POSTFIX d)
