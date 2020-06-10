#include <ncurses.h>
#include <iostream>
#include <clocale>

int main() {

    setlocale(LC_ALL, "");

    initscr();

    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    
    resize_term(25, 50);
    start_color();
    
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    border('|', '|', '-', '-', '+', '+', '+', '+');
    
    attron(COLOR_PAIR(2));
    mvprintw(1, 1, "Welcome To the Tetris Game");
    attroff(COLOR_PAIR(2));
    refresh();
    //getch();

    WINDOW *win1 = newwin(20, 22, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    wattron(win1, COLOR_PAIR(1));
    mvwprintw(win1, 0, 8, "Tetris");
    wattroff(win1, COLOR_PAIR(1));
    
    wattron(win1, COLOR_PAIR(3));
    for (int i = 1; i <= 18; i++) {
        for (int j = 1; j <= 20; j+=2) {
            mvwprintw(win1, i, j, "\u25A1"); // ⎕ \u25A1
        }
    }
    wattroff(win1, COLOR_PAIR(3));
    
    wrefresh(win1);
    //getch();

    WINDOW *win2 = newwin(4, 10, 5, 30);
    wbkgd(win2, COLOR_PAIR(1));
    wattron(win2, COLOR_PAIR(4));
    mvwprintw(win2, 1, 1, "score: ");
    mvwprintw(win2, 2, 1, "0");
    wattroff(win2, COLOR_PAIR(4));
    wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win2);
    //getch();

    WINDOW *win3 = newwin(4, 10, 13, 30);
    wbkgd(win3, COLOR_PAIR(1));
    wattron(win3, COLOR_PAIR(4));
    mvwprintw(win3, 1, 1, "name: ");
    mvwprintw(win3, 2, 1, "user");
    wattroff(win3, COLOR_PAIR(4));
    wborder(win3, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win3);
    getch();

    delwin(win1);
    delwin(win2);
    delwin(win3);
    endwin();

    return 0;
}