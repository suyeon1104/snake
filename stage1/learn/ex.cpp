#include <ncurses.h>
int main()
{
    initscr();

    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();

    printw("UuuuU");
    //refresh();
    getch();
    endwin();
    return 0;
}