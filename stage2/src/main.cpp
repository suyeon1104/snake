#include <iostream>
#include <clocale>
#include <deque>
#include <thread>
#include <chrono>
#include "main.h"
#include "snake.h"
#include "map.h"

using namespace std;


// 화면 초기화 및 키패드 설정, 컬러 팔레트 설정
void initGame()
{
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    resize_term(50, 100);

    start_color();

    // 컬러 팔레트 초기화
    init_pair(CP_BKGR, COLOR_WHITE, COLOR_WHITE);
    init_pair(CP_WALL, COLOR_BLUE, COLOR_WHITE);
    init_pair(CP_IMMUNE_WALL, COLOR_BLACK, COLOR_WHITE);
    init_pair(CP_HEAD, COLOR_CYAN, COLOR_WHITE);
    init_pair(CP_BODY, COLOR_YELLOW, COLOR_WHITE);
    init_pair(CP_GROWTH, COLOR_GREEN, COLOR_WHITE);
    init_pair(CP_POISON, COLOR_RED, COLOR_WHITE);
    init_pair(CP_GATE, COLOR_MAGENTA, COLOR_WHITE);

    init_pair(CP_MESSAGE, COLOR_RED, COLOR_WHITE);
    init_pair(CP_SCORE, COLOR_YELLOW, COLOR_WHITE);
    init_pair(CP_MISSION, COLOR_GREEN, COLOR_WHITE);

    bkgd(COLOR_PAIR(CP_BKGR));

    // Snake Game 메시지 출력
    attron(COLOR_PAIR(CP_MESSAGE));
    mvprintw(1, 1, "Welcome To the Snake Game");
    attroff(COLOR_PAIR(CP_MESSAGE));
    refresh();
}

int main()
{
    initGame();

    Map::setbgMap(Map::mapDatas[0]);
    WINDOW *win1 = newwin(Map::bgMap.getRowSize(), Map::bgMap.getColSize() * 2, 19, 16);
    wbkgd(win1, COLOR_PAIR(CP_BKGR));
    Map::bgMap.display(win1);

    // score board
    WINDOW *win2 = newwin(10, 20, 5, 20);
    int bodyLength = 0, growth = 0, poison = 0, gate = 0;
    wbkgd(win2, COLOR_PAIR(CP_BKGR));
    wattron(win2, COLOR_PAIR(CP_SCORE));
    mvwprintw(win2, 1, 1, "Score Board");
    mvwprintw(win2, 2, 1, "B: ");
    mvwprintw(win2, 3, 1, "+: ");
    mvwprintw(win2, 4, 1, "-: ");
    mvwprintw(win2, 5, 1, "G: ");

    wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(win2, COLOR_PAIR(CP_SCORE));
    wrefresh(win2);

    // mission board
    WINDOW *win3 = newwin(10, 20, 5, 50);
    wbkgd(win3, COLOR_PAIR(CP_BKGR));
    wattron(win3, COLOR_PAIR(CP_MISSION));
    mvwprintw(win3, 1, 1, "Mission: ");
    mvwprintw(win3, 2, 1, "B: ");
    mvwprintw(win3, 3, 1, "+: ");
    mvwprintw(win3, 4, 1, "-: ");
    mvwprintw(win3, 5, 1, "G: ");

    wborder(win3, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(win3, COLOR_PAIR(CP_MISSION));
    wrefresh(win3);

    // Snake 객체 snake 생성
    Snake snake(Map::mapDatas[0]);
    
    // Game loop
    while (true)
    {   
        try {
            snake.tick();
        }
        catch(Failure ex) {
            attron(COLOR_PAIR(CP_MESSAGE));
            mvprintw(17, 20, (ex.message + "가 발생하였습니다.").c_str());
            attroff(COLOR_PAIR(CP_MESSAGE));
            refresh();
            getch();
            break;
        }
        Map::bgMap.display(win1);
        wrefresh(win1);
        snake.display(win1);
        wrefresh(win1);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    // getch() 시 delay하도록 설정
    nodelay(stdscr, false);
    
    // Game over 메시지 출력
    attron(COLOR_PAIR(CP_MESSAGE));
    mvprintw(16, 20, "YOU LOSE...");
    attroff(COLOR_PAIR(CP_MESSAGE));
    refresh();
    getch();
    
    // 게임 종료
    delwin(win1);
    delwin(win2);
    delwin(win3);
    endwin();

    return 0;
}