#include <iostream>
#include <clocale>
#include <deque>
#include <thread>
#include <chrono>
#include "main.h"
#include "snake.h"
#include "map.h"
#include "board.cpp"

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
    // 사용할 gate 설정
    Gate aGate;
    Gate bGate;
    // stage row,col을 임의로 받을대 사용
    int temrow,temcol;

    Map::setbgMap(Map::mapData[Map::current_map_index]);
    int start_pos = 15;
    WINDOW *win1 = newwin(Map::bgMap.getRowSize(), Map::bgMap.getColSize() * 2, start_pos, start_pos);
    wbkgd(win1, COLOR_PAIR(CP_BKGR));
    Map::bgMap.display(win1);

    // Snake 객체 snake 생성
    Snake snake(Map::mapData[Map::current_map_index]);
    draw_board(snake);

    // Game loop
    while (true)
    {
        try
        {
            snake.tick();
        }
        catch (Failure ex)
        {
            attron(COLOR_PAIR(CP_MESSAGE));
            mvprintw(WINDOW_MARGIN - 1, WINDOW_MARGIN, (ex.message + "가 발생하였습니다.").c_str());
            attroff(COLOR_PAIR(CP_MESSAGE));
            refresh();
            getch();
            break;
        }
        //gate를 통과중이면 아무것도 하지 않음
        if(snake.getGatepass() == true)
        {
            ;
        }
        //통과중이 지 않다면 게이트를 랜덤생성함
        else if (snake.getGatepass() == false)
            {
            //stage 가로 세로를 받음
            temrow = Map::bgMap.getColSize();
            temcol = Map::bgMap.getRowSize();
            //하나씩 게이트 생성, 두 게이트가 겹치지 않도록
            aGate = snake.RandomGate(Map::mapData[Map::current_map_index],bGate.x,bGate.y,temrow,temcol);
            snake.setGate1(aGate.x,aGate.y);
            bGate = snake.RandomGate(Map::mapData[Map::current_map_index],aGate.x,aGate.y,temrow,temcol);
            snake.setGate2(bGate.x,bGate.y);
            //원래 맵으로 정리
            Map::bgMap.setbgMapraw(Map::mapData[Map::current_map_index]);
            //게이트가 적용된 맵으로 설정
            Map::bgMap.setbgMapgate(Map::mapData[Map::current_map_index],aGate.x,aGate.y,bGate.x,bGate.y);
            //이제부터 snake가 gate를 통과중이니 gatepass를 true로함
            snake.setGatePass(true);
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
    mvprintw(WINDOW_MARGIN - 3, WINDOW_MARGIN, "YOU LOSE...");
    attroff(COLOR_PAIR(CP_MESSAGE));
    refresh();
    getch();

    endwin();

    return 0;
}
