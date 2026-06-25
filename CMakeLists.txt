cmake_minimum_required(VERSION 3.19)
project(BookManagementSystem LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql LinguistTools)

qt_standard_project_setup()

qt_add_executable(BookManagementSystem
    WIN32 MACOSX_BUNDLE
    main.cpp
    bookmanagementsystem.cpp
    bookmanagementsystem.h
    bookmanagementsystem.ui
    model/admin.cpp
    model/admin.h
    model/book.cpp
    model/book.h
    model/bookcopy.cpp
    model/bookcopy.h
    model/fine.cpp
    model/fine.h
    model/loan.cpp
    model/loan.h
    model/location.cpp
    model/location.h
    model/patron.cpp
    model/patron.h
    model/reservation.cpp
    model/reservation.h
    model/user.cpp
    model/user.h
    model/date.h
    model/date.cpp
    dao/bookdao.h dao/bookdao.cpp
    dao/bookcopydao.h dao/bookcopydao.cpp
    dao/userdao.h dao/userdao.cpp
    dao/loandao.h dao/loandao.cpp
    dao/finedao.h dao/finedao.cpp
    dao/reservationdao.h dao/reservationdao.cpp

)

qt_add_translations(
    TARGETS BookManagementSystem
    TS_FILES BookManagementSystem_en_AS.ts
)

target_link_libraries(BookManagementSystem
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

install(TARGETS BookManagementSystem
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BookManagementSystem
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
