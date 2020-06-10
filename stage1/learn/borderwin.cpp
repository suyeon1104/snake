#include <ncurses.h>
int main()
{
    initscr();
    box(stdscr, 0, 0); // 윈도우의 경계를 표현한다
    refresh();

    getch();
    endwin();
    
    return 0;
}