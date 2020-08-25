cmake_minimum_required(VERSION 3.13)
project(connectN C)

set(CMAKE_C_STANDARD 11)

add_executable(connect main.c win.h move.h win.c board.h board.c CursorTrakedWindow.h InputValidation.c InputValidation.h move.c CursorTrakedWindow.c)

set(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
target_link_libraries(connect PRIVATE ${CURSES_LIBRARIES})
target_include_directories(connect PRIVATE ${CURSES_INCLUDE_DIRS})
