#include <ncurses.h>
#include <iostream>
#include <clocale>

int main() {

    setlocale(LC_ALL, "");

    initscr();

    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    
    resize_term(50, 100);
    start_color();
    
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_WHITE);
    init_pair(4, COLOR_YELLOW, COLOR_WHITE);
    
    // 바탕 색
    init_pair(5, COLOR_WHITE, COLOR_WHITE); // 0
    // 변 색
    init_pair(6, COLOR_CYAN, COLOR_WHITE); // 1
    // 모서리 색
    init_pair(7, COLOR_BLACK, COLOR_WHITE); // 2
    // HEAD 색
    init_pair(8, COLOR_RED, COLOR_WHITE); // 3
    // BODY 색
    init_pair(9, COLOR_YELLOW, COLOR_WHITE); // 4

    // GROWTH ITEM 색
    init_pair(10, COLOR_GREEN, COLOR_WHITE); // 5
    // POISON ITEM 색
    init_pair(11, COLOR_BLUE, COLOR_WHITE); // 6
    // GATE 색
    init_pair(11, COLOR_MAGENTA, COLOR_WHITE); // 7

    bkgd(COLOR_PAIR(1));
    
    // map 초기화
    int map[30][60] = { 0 };
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 60; j+=2) {
            if (i == 0 || j == 0 || i == 29 || j == 58) {
                map[i][j] = 1;
            } else {
                map[i][j] = 0;
            }
        }
    }
    map[0][0] = 2;
    map[0][58] = 2;
    map[29][0] = 2;
    map[29][58] = 2;

    map[18][22] = 3;
    map[18][23] = 3;
    map[18][24] = 4;
    map[18][25] = 4; 
    map[18][26] = 4;
    map[18][27] = 4;

    attron(COLOR_PAIR(2));
    mvprintw(1, 1, "Welcome To the Snake Game");
    attroff(COLOR_PAIR(2));
    refresh();

    WINDOW *win1 = newwin(30, 60, 17, 15);
    wbkgd(win1, COLOR_PAIR(5));
    
    for (int i = 0; i <= 29; i++) {
        for (int j = 0; j <= 59; j+=2) {
            if (map[i][j] == 0) {
                wattron(win1, COLOR_PAIR(5)); // 바탕색
                mvwprintw(win1, i, j, "\u25A0");
                wattroff(win1, COLOR_PAIR(5));
            }
            if (map[i][j] == 1) {
                wattron(win1, COLOR_PAIR(6)); // 변 색
                mvwprintw(win1, i, j, "\u25A0");
                wattroff(win1, COLOR_PAIR(6));
            }
            if (map[i][j] == 2) {
                wattron(win1, COLOR_PAIR(7)); // 모서리 색
                mvwprintw(win1, i, j, "\u25A0");
                wattroff(win1, COLOR_PAIR(7));
            }
            if (map[i][j] == 3) {
                wattron(win1, COLOR_PAIR(8)); // HEAD 색
                mvwprintw(win1, i, j, "\u25CF");
                wattroff(win1, COLOR_PAIR(8));
            }
            if (map[i][j] == 4) {
                wattron(win1, COLOR_PAIR(9)); // BODY 색
                mvwprintw(win1, i, j, "\u25CF");
                wattroff(win1, COLOR_PAIR(9));
            }
        }
    }
    
    wrefresh(win1);

    // score board
    WINDOW *win2 = newwin(10, 20, 5, 20);
    int B = 0, plus = 0, minus = 0, G = 0;
    wbkgd(win2, COLOR_PAIR(1));
    wattron(win2, COLOR_PAIR(4));
    mvwprintw(win2, 1, 1, "Score Board");
    mvwprintw(win2, 2, 1, "B: ");
    mvwprintw(win2, 3, 1, "+: ");
    mvwprintw(win2, 4, 1, "-: ");
    mvwprintw(win2, 5, 1, "G: ");

    wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(win2, COLOR_PAIR(4));
    wrefresh(win2);

    // mission board
    WINDOW *win3 = newwin(10, 20, 5, 50);
    wbkgd(win3, COLOR_PAIR(1));
    wattron(win3, COLOR_PAIR(4));
    mvwprintw(win3, 1, 1, "Mission: ");
    mvwprintw(win3, 2, 1, "B: ");
    mvwprintw(win3, 3, 1, "+: ");
    mvwprintw(win3, 4, 1, "-: ");
    mvwprintw(win3, 5, 1, "G: ");
    
    wborder(win3, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(win3, COLOR_PAIR(4));
    wrefresh(win3);

    delwin(win1);
    delwin(win2);
    delwin(win3);
    endwin();

    return 0;
}