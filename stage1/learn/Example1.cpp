#include <ncurses.h>
#include <iostream>
int main()
{
    int row, col;

    std::cin >> row >> col;
    
    initscr();
    resize_term(row, col);
    mvprintw(3,4,"C++ programming with ncurses");
    
    refresh();
    getch();
    endwin();
    
    return 0;
}