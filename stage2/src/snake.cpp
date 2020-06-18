#include "snake.h"
#include "main.h"
#include "map.h"
#include <ncurses.h>
#include <iostream>
#include <cstdlib>

//Snake의 생성자로서, mapData로부터 snake의 Head를 찾아낸 뒤, findBody를 이용하여 Snake의 나머지 Body들을 찾아내고, snake의 초기 방향을 검출함.
Snake::Snake(vector<vector<int>> mapData)
{
    for (int i = 0; i < mapData.size(); i++)
    {
        for (int j = 0; j < mapData[0].size(); j++)
        {
            if (mapData[i][j] == 3)
            {
                snakeData.push_back(vector<int>({i, j}));
                goto foundHead;
            }
        }
    }
foundHead:
    findBody(mapData);

    // snake의 초기 방향 검출
    
    if (snakeData.size() == 1)
    {
        dir = LEFT;
    }
    else
    {
        if (snakeData[0][0] > snakeData[1][0])
        {
            dir = DOWN;
        }
        else if (snakeData[0][0] < snakeData[1][0])
        {
            dir = UP;
        }
        else if (snakeData[0][1] > snakeData[1][1])
        {
            dir = RIGHT;
        }
        else if (snakeData[0][1] < snakeData[1][1])
        {
            dir = LEFT;
        }
    }
}

// mapData로부터 snake의 body를 재귀적으로 찾아내기
void Snake::findBody(vector<vector<int>> &mapData)
{
    int nrow = mapData.size();
    int ncol = mapData[0].size();
    int r = snakeData.back()[0];
    int c = snakeData.back()[1];
    mapData[r][c] = 0;
    if (c + 1 < ncol && mapData[r][c + 1] == 4)
    {
        snakeData.push_back(vector<int>({r, c + 1}));
        findBody(mapData);
    }
    else if (c - 1 >= 0 && mapData[r][c - 1] == 4)
    {
        snakeData.push_back(vector<int>({r, c - 1}));
        findBody(mapData);
    }
    else if (r + 1 < nrow && mapData[r + 1][c] == 4)
    {
        snakeData.push_back(vector<int>({r + 1, c}));
        findBody(mapData);
    }
    else if (r - 1 >= 0 && mapData[r - 1][c] == 4)
    {
        snakeData.push_back(vector<int>({r - 1, c}));
        findBody(mapData);
    }
    else
    {
        return;
    }
}

// 한 tick 내에 수행하는 snake의 동작 정의
void Snake::tick()
{
    int headR = snakeData[0][0];
    int headC = snakeData[0][1];
    nodelay(stdscr, true);
    key = getch();

    // 새로운 key 입력이 없으면 HEAD는 예전 key 입력에 대한 동작을 반복함
    if (key == -1)
    {
        if (dir == UP)
        {
            headR--;
        }
        if (dir == LEFT)
        {
            headC--;
        }
        if (dir == DOWN)
        {
            headR++;
        }
        if (dir == RIGHT)
        {
            headC++;
        }
    }

    //새로운 key 입력에 따라 HEAD를 이동함
    if (key == KEY_UP)
    {
        headR--;
        dir = UP;
    }
    if (key == KEY_LEFT)
    {
        headC--;
        dir = LEFT;
    }
    if (key == KEY_DOWN)
    {
        headR++;
        dir = DOWN;
    }
    if (key == KEY_RIGHT)
    {
        headC++;
        dir = RIGHT;
    }

    checkWallConflict(headR, headC);
    
    // 자취 따라가기. BODY는 자신의 앞에 있는 BODY나 HEAD를 따라간다.
    snakeData.push_front(vector<int>({headR, headC}));
    snakeData.pop_back();
    
    checkBodyConflict(headR, headC);
}

// Head의 위치릍 통해 Head가 곧바로 mapData에 있는 Wall과 부딪힐 것인지 미리 체크한다.
void Snake::checkWallConflict(int headR, int headC) {
    if (Map::bgMap[headR][headC] == 1) {
        throw Failure("wall conflict");
    }
}

// Head의 위치릍 통해 Head가 곧바로 mapData에 있는 Body와 부딪힐 것인지 미리 체크한다.
void Snake::checkBodyConflict(int headR, int headC) {
    for (int i = 1; i < snakeData.size(); i++) {
        if (headR == snakeData[i][0] && headC == snakeData[i][1]) {
            throw Failure("body conflict");
        }
    }
}

// snake를 화면에 표시. snake를 그려주기 전에 snake가 지나간 자국들을 배경 색으로 칠해서 지워준다.
void Snake::display(WINDOW *win)
{

    wattron(win, COLOR_PAIR(CP_BKGR));
    mvwprintw(win, snakeData[0][0], snakeData[0][1] * 2, " ");
    mvwprintw(win, snakeData[0][0], snakeData[0][1] * 2 + 1, " ");
    wattroff(win, COLOR_PAIR(CP_BKGR));
    wattron(win, COLOR_PAIR(CP_HEAD)); // HEAD 색
    mvwprintw(win, snakeData[0][0], snakeData[0][1] * 2, "\u25CF");
    wattroff(win, COLOR_PAIR(CP_HEAD));
    for (int i = 1; i < snakeData.size(); i++)
    {
        wattron(win, COLOR_PAIR(CP_BKGR));
        mvwprintw(win, snakeData[i][0], snakeData[i][1] * 2, " ");
        mvwprintw(win, snakeData[i][0], snakeData[i][1] * 2 + 1, " ");
        wattroff(win, COLOR_PAIR(CP_BKGR));
        wattron(win, COLOR_PAIR(CP_BODY)); // BODY 색
        mvwprintw(win, snakeData[i][0], snakeData[i][1] * 2, "\u25CF");
        wattroff(win, COLOR_PAIR(CP_BODY));
    }
}