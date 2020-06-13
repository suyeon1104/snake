#include <ncurses.h>
#include <iostream>
#include <clocale>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <thread>
#include <chrono> 

using namespace std;


void initScreen()
{
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

    attron(COLOR_PAIR(2));
    mvprintw(1, 1, "Welcome To the Snake Game");
    attroff(COLOR_PAIR(2));
    refresh();

}

// map 초기화
class Map
{
    vector<vector<int>> mapData;

public:
    Map(const vector<vector<int>> &mapData) : mapData(mapData)
    {
        
    }
    int getRowSize() {
        return mapData.size();
    }
    int getColSize() {
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
                    wattron(win, COLOR_PAIR(5)); // 바탕색
                    mvwprintw(win, i, j*2, "M");
                    mvwprintw(win, i, j*2+1, "M");
                    wattroff(win, COLOR_PAIR(5));
                }

                if (mapData[i][j] == 1)
                {
                    wattron(win, COLOR_PAIR(6)); // 변 색
                    mvwprintw(win, i, j * 2, "\u25A0");
                    //mvwprintw(win, i, j+1, "\u25A0");
                    wattroff(win, COLOR_PAIR(6));
                }
                if (mapData[i][j] == 2)
                {
                    wattron(win, COLOR_PAIR(7)); // 모서리 색
                    mvwprintw(win, i, j * 2, "\u25A0");
                    //mvwprintw(win, i, j+1, "\u25A0");
                    wattroff(win, COLOR_PAIR(7));
                }
                /*
                if (mapData[i][j] == 3)
                {
                    wattron(win, COLOR_PAIR(8)); // HEAD 색
                    mvwprintw(win, i, j * 2, "\u25CF");
                    // mvwprintw(win, i, j+1, "\u25CF");
                    wattroff(win, COLOR_PAIR(8));
                }
                if (mapData[i][j] == 4)
                {
                    wattron(win, COLOR_PAIR(9)); // BODY 색
                    mvwprintw(win, i, j * 2, "\u25CF");
                    //mvwprintw(win, i, j+1, "\u25CF");
                    wattroff(win, COLOR_PAIR(9));
                }
                */
            }
        }
        wrefresh(win);
    }

};


class Snake {
    bool Fail = false;
    int positionR = 7, positionC = 7;
    vector<vector<int>> snakeData = vector<vector<int>>({ { positionR, positionC }, {positionR, positionC+1}, {positionR, positionC+2} });
public:
    Snake() : positionR(7), positionC(7) {
    }
    int key, key1;
    void tick()
    {
        int t1 = snakeData[0][0];
        int t2 = snakeData[0][1];
        nodelay(stdscr, true);
        key = getch();
        // 새로운 key 입력이 없으면 HEAD는 예전 key 입력에 대한 동작을 반복함
        if (key == -1) {
            if (key1 == KEY_UP) {
                snakeData[0][0]--;
            }
            if (key1 == KEY_LEFT) {
                snakeData[0][1]--;
            }
            if (key1 == KEY_DOWN) {
                snakeData[0][0]++;
            }
            if (key1 == KEY_RIGHT) {
                snakeData[0][1]++;
            }
        }

        //새로운 key 입력에 따라 HEAD를 이동함
        if (key == KEY_UP) {
            if (key1 == KEY_DOWN) {
                Fail = true;
            }
            snakeData[0][0]--;
            key1 = key;
        }
        if (key == KEY_LEFT) {
            if (key1 == KEY_RIGHT) {
                Fail = true;
            }
            snakeData[0][1]--;
            key1 = key;
        }
        if (key == KEY_DOWN) {
            if (key1 == KEY_UP) {
                Fail = true;
            }
            snakeData[0][0]++;
            key1 = key;
        }
        if (key == KEY_RIGHT) {
            if (key1 == KEY_LEFT) {
                Fail = true;
            }
            snakeData[0][1]++;
            key1 = key;
        }

        // 자취 따라가기. BODY는 자신의 앞에 있는 BODY나 HEAD를 따라간다.
        for (int i  = snakeData.size()-1; i > 1; i--) {
            snakeData[i][0] = snakeData[i-1][0];
            snakeData[i][1] = snakeData[i-1][1];
        }
        snakeData[1][0] = t1;
        snakeData[1][1] = t2;
    }

    bool getFail() {
        return Fail;
    }
    /*
    int& getSnakeHead() {
        int head[2] = {snakeData[0][0], snakeData[0][1]};
        return *head;
    }
    */
    void display(WINDOW *win) {
        
        wattron(win, COLOR_PAIR(5));
        mvwprintw(win, snakeData[0][0], snakeData[0][1]*2, " ");
        mvwprintw(win, snakeData[0][0], snakeData[0][1]*2+1, " ");
        wattroff(win, COLOR_PAIR(5));
        wattron(win, COLOR_PAIR(8)); // HEAD 색
        mvwprintw(win, snakeData[0][0], snakeData[0][1]*2, "\u25CF");
        wattroff(win, COLOR_PAIR(8));
        for (int i = 1; i < snakeData.size(); i++) {
            wattron(win, COLOR_PAIR(5)); 
            mvwprintw(win, snakeData[i][0], snakeData[i][1]*2, " ");
            mvwprintw(win, snakeData[i][0], snakeData[i][1]*2+1, " ");
            wattroff(win, COLOR_PAIR(5)); 
            wattron(win, COLOR_PAIR(9)); // BODY 색
            mvwprintw(win, snakeData[i][0], snakeData[i][1]*2, "\u25CF");
            wattroff(win, COLOR_PAIR(9));
        }
        //wrefresh(win);
    }

};

class Head : public Snake {

};
class Body : public Snake {

};


int main()
{
    initScreen();
    Map map = vector<vector<int>>(
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
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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
    );
    
    WINDOW *win1 = newwin(map.getRowSize(), map.getColSize() * 2, 18, 16);
    wbkgd(win1, COLOR_PAIR(1));
    map.display(win1);
    
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

    //bool gameOn = true;
    Snake snake;
    // Game loop
    int i = 0;
    while (true) {

        //getch();
        if (snake.getFail()) {
            break;
        }
        snake.tick();
        map.display(win1);
        wrefresh(win1);
        snake.display(win1);
        wrefresh(win1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    nodelay(stdscr, false);
    attron(COLOR_PAIR(8));
    //int h = snake.getSnakeHead();
    //mvprintw(h[0]-1, h[1], "YOU LOSE...");
    mvprintw(16, 30, "YOU LOSE...");
    attroff(COLOR_PAIR(8));
    refresh();
    getch();
    delwin(win1);
    delwin(win2);
    delwin(win3);
    endwin();

    return 0;
}