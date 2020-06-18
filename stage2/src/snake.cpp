#include <ncurses.h>
#include <iostream>
#include <clocale>
#include <vector>
#include <deque>
#include <time.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "snake.h"

using namespace std;

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

    attron(COLOR_PAIR(CP_MESSAGE));
    mvprintw(1, 1, "Welcome To the Snake Game");
    attroff(COLOR_PAIR(CP_MESSAGE));
    refresh();
}

// 배경 맵 클래스
class Map
{
    vector<vector<int>> mapData;

public:
    Map(const vector<vector<int>> &inputMapData) : mapData(inputMapData)
    {
        int nrow = mapData.size();
        int ncol = mapData[0].size();
        for (int i = 0; i < nrow; i++)
        {
            for (int j = 0; j < ncol; j++)
            {
                if (mapData[i][j] != 0 && mapData[i][j] != 1 && mapData[i][j] != 2) {
                    mapData[i][j] = 0;
                }
            }
        }
    }
    int getRowSize()
    {
        return mapData.size();
    }
    int getColSize()
    {
        return mapData[0].size();
    }
    void display(WINDOW *win)
    {
        int nrow = mapData.size();
        int ncol = mapData[0].size();
        for (int i = 0; i < nrow; i++)
        {
            for (int j = 0; j < ncol; j++)
            {
                if (mapData[i][j] == 0)
                {
                    wattron(win, COLOR_PAIR(CP_BKGR)); // 바탕색
                    mvwprintw(win, i, j * 2, "M");
                    mvwprintw(win, i, j * 2 + 1, "M");
                    wattroff(win, COLOR_PAIR(CP_BKGR));
                }
                else if (mapData[i][j] == 1)
                {
                    wattron(win, COLOR_PAIR(CP_WALL)); // 변 색
                    mvwprintw(win, i, j * 2, "\u25A0");
                    wattroff(win, COLOR_PAIR(CP_WALL));
                }
                else if (mapData[i][j] == 2)
                {
                    wattron(win, COLOR_PAIR(CP_IMMUNE_WALL)); // 모서리 색
                    mvwprintw(win, i, j * 2, "\u25A0");
                    wattroff(win, COLOR_PAIR(CP_IMMUNE_WALL));
                }
            }
        }
        wrefresh(win);
    }
};

// Snake 클래스
class Snake
{
    enum Direction {
        LEFT, RIGHT, UP, DOWN
    };
    Direction dir;
    bool Fail = false;
    deque<vector<int>> snakeData = deque<vector<int>>();

public:
    void findBody(vector<vector<int>> &mapData) {
        int nrow = mapData.size();
        int ncol = mapData[0].size();
        int r = snakeData.back()[0];
        int c = snakeData.back()[1];
        mapData[r][c] = 0;
        if (c+1 < ncol && mapData[r][c+1] == 4) {
            snakeData.push_back(vector<int>({r, c+1}));
            findBody(mapData);
        } else if (c-1 >= 0 && mapData[r][c-1] == 4) {
            snakeData.push_back(vector<int>({r, c-1}));
            findBody(mapData);
        } else if (r+1 < nrow && mapData[r+1][c] == 4) {
            snakeData.push_back(vector<int>({r+1, c}));
            findBody(mapData);
        } else if (r-1 >= 0 && mapData[r-1][c] == 4) {
            snakeData.push_back(vector<int>({r-1, c}));
            findBody(mapData);
        } else {
            return;
        }
    }
    Snake(vector<vector<int>> mapData, WINDOW* win)
    {
        for (int i = 0; i < mapData.size(); i++) {
            for (int j = 0; j < mapData[0].size(); j++) {
                if (mapData[i][j] == 3) {
                    snakeData.push_back(vector<int>({i, j}));
                    goto foundHead;
                }
            }
        }
        foundHead:
            int r = snakeData.back()[0];
            int c = snakeData.back()[1];
            findBody(mapData);
            
            if (snakeData.size() == 1) {
                dir = LEFT; 
            } else {
                if (snakeData[0][0] > snakeData[1][0]) {
                    dir = DOWN;
                }
                else if (snakeData[0][0] < snakeData[1][0]) {
                    dir = UP;
                }
                else if (snakeData[0][1] > snakeData[1][1]) {
                    dir = RIGHT;
                }
                else if (snakeData[0][1] < snakeData[1][1]) {
                    dir = LEFT;
                }
            }
    }
    int key;
    void tick()
    {
        //cout << snakeData.size() << endl;
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
            if (dir == DOWN)
            {
                Fail = true;
            }
            headR--;
            dir = UP;
        }
        if (key == KEY_LEFT)
        {
            if (dir == RIGHT)
            {
                Fail = true;
            }
            headC--;
            dir = LEFT;
        }
        if (key == KEY_DOWN)
        {
            if (dir == UP)
            {
                Fail = true;
            }
            headR++;
            dir = DOWN;
        }
        if (key == KEY_RIGHT)
        {
            if (dir == LEFT)
            {
                Fail = true;
            }
            headC++;
            dir = RIGHT;
        }

        // 자취 따라가기. BODY는 자신의 앞에 있는 BODY나 HEAD를 따라간다.
        snakeData.push_front(vector<int>({headR, headC}));
        snakeData.pop_back();
    }

    bool getFail()
    {
        return Fail;
    }
    void display(WINDOW *win)
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
};

int main()
{
    initGame();
    vector<vector<int>> mapDatas[] = {
        {
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        }
    };
    Map bgMap(mapDatas[0]);
    WINDOW *win1 = newwin(bgMap.getRowSize(), bgMap.getColSize() * 2, 18, 16);
    wbkgd(win1, COLOR_PAIR(CP_BKGR));
    bgMap.display(win1);

    // score board
    WINDOW *win2 = newwin(10, 20, 5, 20);
    int B = 0, plus = 0, minus = 0, G = 0;
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

    Snake snake(mapDatas[0], win1);
    // Game loop
    while (true)
    {
        if (snake.getFail())
        {
            break;
        }
        snake.tick();
        bgMap.display(win1);
        wrefresh(win1);
        snake.display(win1);
        wrefresh(win1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    nodelay(stdscr, false);
    attron(COLOR_PAIR(CP_MESSAGE));
    mvprintw(16, 30, "YOU LOSE...");
    attroff(COLOR_PAIR(CP_MESSAGE));
    refresh();
    getch();
    delwin(win1);
    delwin(win2);
    delwin(win3);
    endwin();

    return 0;
}