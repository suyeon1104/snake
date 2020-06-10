#include <ncurses.h>
#include <clocale>
int main()
{
    setlocale(LC_ALL, "");
    char key;
    char userName[8];

    initscr();

    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();

    printw("User name: ");
    scanw("%s", userName);

    printw("%s\n", userName);
    printw("키 입력시 화면이 지워집니다");
    refresh();

    getch();
    clear();
    refresh();

    getch();
    endwin();
    return 0;
}