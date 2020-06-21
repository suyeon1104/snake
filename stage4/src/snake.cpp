#include "snake.h"
#include "main.h"
#include "map.h"
#include <ncurses.h>
#include <iostream>
#include <cstdlib>



Snake::Snake(vector<vector<int>> mapData)
{
    Gate1.x=1;
    Gate1.y=0;
    Gate2.x=3;
    Gate2.y=0;
    // mapData로부터 snake의 Head 찾아내기
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

    // Snake의 나머지 Body들을 찾아냄.
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


void Snake::tick(vector<vector<int>> mapData)
{
    Gate nexthead;
    int headR = snakeData[0][0];
    int headC = snakeData[0][1];
    nexthead.x = headR;
    nexthead.y = headC;
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
    nexthead = checkGatein(headR,headC,mapData);
    if (headR!= nexthead.x && headC != nexthead.y)
    {
        gatesnakebody = snakelength();
        gatetry = 0;
        Gatepass = true;
    }
    // 자취 따라가기. BODY는 자신의 앞에 있는 BODY나 HEAD를 따라간다.
    snakeData.push_front(vector<int>({nexthead.x, nexthead.y}));
    snakeData.pop_back();

    checkBodyConflict(headR, headC);
    gatetry++;
    if(gatetry == gatesnakebody || gatetry == -1)
    {
        Gatepass = false;
    }
}


void Snake::checkWallConflict(int headR, int headC) {
    if (Map::bgMap[headR][headC] == 1) {
        throw Failure("wall conflict");
    }
}


void Snake::checkBodyConflict(int headR, int headC) {
    for (int i = 1; i < snakeData.size(); i++) {
        if (headR == snakeData[i][0] && headC == snakeData[i][1]) {
            throw Failure("body conflict");
        }
    }
}

// gate check
Gate Snake::checkGatein(int headR, int headC,vector<vector<int>> &mapData){
    Gate tem1 = getGate1();
    Gate tem2 = getGate2();
    Gate head;
    head.x = headR;
    head.y = headC;
    if (headR == tem1.x && headC == tem1.y)
    {
         if (dir == UP)
        {   
            //위 검사
            if(tem2.x !=0 && mapData[tem2.x-1][tem2.y] == 0){
                head.x = tem2.x-1;
                head.y = tem2.y;
                return head;
            }
            // 오른쪽 검사
            else if(tem2.y !=20 && mapData[tem2.x][tem2.y+1] == 0){
                head.x = tem2.x;
                head.y = tem2.y+1;
                dir = RIGHT;
                return head;
            }
            //왼쪽 검사
            else if(tem2.y !=0 && mapData[tem2.x][tem2.y-1] == 0 ){
                head.x = tem2.x;
                head.y = tem2.y-1;
                dir = LEFT;
                return head;
            }
            // 밑 검사
            else if(tem2.x !=20 && mapData[tem2.x+1][tem2.y] == 0 ){
                head.x = tem2.x+1;
                head.y = tem2.y;
                dir = DOWN;
                return head;
            }
        }
        if (dir == LEFT)
        {   
            //왼쪽 검사
            if(tem2.y !=0 && mapData[tem2.x][tem2.y-1] == 0 ){
                head.x = tem2.x;
                head.y = tem2.y-1;
                return head;
            }
            //위 검사
            else if(tem2.x !=0 && mapData[tem2.x-1][tem2.y] == 0 ){
                head.x = tem2.x-1;
                head.y = tem2.y;
                dir = UP;
                return head;
            }
            // 밑 검사
            else if(tem2.x !=20 && mapData[tem2.x+1][tem2.y] == 0 ){
                head.x = tem2.x+1;
                head.y = tem2.y;
                dir = DOWN;
                return head;
            }
            // 오른쪽 검사
            else if(tem2.y !=20 && mapData[tem2.x][tem2.y+1] == 0 ){
                head.x = tem2.x;
                head.y = tem2.y+1;
                dir = RIGHT;
                return head;
            }
               
        }
        if (dir == DOWN)
        {
            // 밑 검사
            if(tem2.x !=20 && mapData[tem2.x+1][tem2.y] == 0 ){
                head.x = tem2.x+1;
                head.y = tem2.y;
                return head;
            }
            //왼쪽 검사
            else if(tem2.y !=0 && mapData[tem2.x][tem2.y-1] == 0 ){
                head.x = tem2.x;
                head.y = tem2.y-1;
                dir = LEFT;
                return head;
            }
            // 오른쪽 검사
            else if(tem2.y !=20 && mapData[tem2.x][tem2.y+1] == 0 ){
                head.x = tem2.x;
                head.y = tem2.y+1;
                dir = RIGHT;
                return head;
            }
            //위 검사
            else if(tem2.x !=0 && mapData[tem2.x-1][tem2.y] == 0 ){
                head.x = tem2.x-1;
                head.y = tem2.y;
                dir = UP;
                return head;
            }
            
        }
        if (dir == RIGHT)
        {
            // 오른쪽 검사
            if(tem2.y !=20 && mapData[tem2.x][tem2.y+1] == 0 ){
                head.x = tem2.x;
                head.y = tem2.y+1;
                return head;
            }
            // 밑 검사
            else if(tem2.x !=20 && mapData[tem2.x+1][tem2.y] == 0 ){
                head.x = tem2.x+1;
                head.y = tem2.y;
                dir = DOWN;
                return head;
            }
            //위 검사
            else if(tem2.x !=0 && mapData[tem2.x-1][tem2.y] == 0 ){
                head.x = tem2.x-1;
                head.y = tem2.y;
                dir = UP;
                return head;
            }
            //왼쪽 검사
            else if(tem2.y !=0 && mapData[tem2.x][tem2.y-1] == 0 ){
                head.x = tem2.x;
                head.y = tem2.y-1;
                dir = LEFT;
                return head;
            }
        }

        
    }
    else if(headR == tem2.x && headC == tem2.y)
    {
        if (dir == UP)
        {   
            //위 검사
            if(tem1.x !=0 && mapData[tem1.x-1][tem1.y] == 0 ){
                head.x = tem1.x-1;
                head.y = tem1.y;
                return head;
            }
            // 오른쪽 검사
            else if(tem1.y !=20 && mapData[tem1.x][tem1.y+1] == 0 ){
                head.x = tem1.x;
                head.y = tem1.y+1;
                dir = RIGHT;
                return head;
            }
            //왼쪽 검사
            else if(tem1.y !=0 && mapData[tem1.x][tem1.y-1] == 0 ){
                head.x = tem1.x;
                head.y = tem1.y-1;
                dir = LEFT;
                return head;
            }
            // 밑 검사
            else if(tem1.x !=20 && mapData[tem1.x+1][tem1.y] == 0 ){
                head.x = tem1.x+1;
                head.y = tem1.y;
                dir = DOWN;
                return head;
            }
        }
        if (dir == LEFT)
        {   
            //왼쪽 검사
            if(tem1.y !=0 && mapData[tem1.x][tem1.y-1] == 0 ){
                head.x = tem1.x;
                head.y = tem1.y-1;
                return head;
            }
            //위 검사
            else if(tem1.x !=0 && mapData[tem1.x-1][tem1.y] == 0 ){
                head.x = tem1.x-1;
                head.y = tem1.y;
                dir = UP;
                return head;
            }
            // 밑 검사
            else if(tem1.x !=20 && mapData[tem1.x+1][tem1.y] == 0 ){
                head.x = tem1.x+1;
                head.y = tem1.y;
                dir = DOWN;
                return head;
            }
            // 오른쪽 검사
            else if(tem1.y !=20 && mapData[tem1.x][tem2.y+1] == 0 ){
                head.x = tem1.x;
                head.y = tem1.y+1;
                dir = RIGHT;
                return head;
            }
               
        }
        if (dir == DOWN)
        {
            // 밑 검사
            if(tem1.x !=20 && mapData[tem1.x+1][tem1.y] == 0 ){
                head.x = tem1.x+1;
                head.y = tem1.y;
                return head;
            }
            //왼쪽 검사
            else if(tem1.y !=0 && mapData[tem1.x][tem1.y-1] == 0 ){
                head.x = tem1.x;
                head.y = tem1.y-1;
                dir = LEFT;
                return head;
            }
            // 오른쪽 검사
            else if(tem1.y !=20 && mapData[tem1.x][tem1.y+1] == 0 ){
                head.x = tem1.x;
                head.y = tem1.y+1;
                dir = RIGHT;
                return head;
            }
            //위 검사
            else if(tem1.x !=0 && mapData[tem1.x-1][tem1.y] == 0 ){
                head.x = tem1.x-1;
                head.y = tem1.y;
                dir = UP;
                return head;
            }
            
        }
        if (dir == RIGHT)
        {
            // 오른쪽 검사
            if(tem1.y !=20 && mapData[tem1.x][tem1.y+1] == 0 ){
                head.x = tem1.x;
                head.y = tem1.y+1;
                return head;
            }
            // 밑 검사
            else if(tem1.x !=20 && mapData[tem1.x+1][tem1.y] == 0 ){
                head.x = tem1.x+1;
                head.y = tem1.y;
                dir = DOWN;
                return head;
            }
            //위 검사
            else if(tem1.x !=0 && mapData[tem1.x-1][tem1.y] == 0 ){
                head.x = tem1.x-1;
                head.y = tem1.y;
                dir = UP;
                return head;
            }
            //왼쪽 검사
            else if(tem1.y !=0 && mapData[tem1.x][tem1.y-1] == 0){
                head.x = tem1.x;
                head.y = tem1.y-1;
                dir = LEFT;
                return head;
            }
        }
    }
    return head;

}


void Snake::display(WINDOW *win)
{
    // snake의 Head를 그려주기 전에 snake가 새로 그릴 자리들을 배경 색으로 칠해줌.
    // 그렇지 않으면 background를 칠해줘도 snake가 지나간 자국이 남음.
    wattron(win, COLOR_PAIR(CP_BKGR));
    mvwprintw(win, snakeData[0][0], snakeData[0][1] * 2, " ");
    mvwprintw(win, snakeData[0][0], snakeData[0][1] * 2 + 1, " ");
    wattroff(win, COLOR_PAIR(CP_BKGR));
    
    // snake의 Head 칠해주기
    // 비 아스키 문자를 출력하면 screen 상에 두 칸을 차지하므로 가로를 두 배로 늘려서 특수문자 출력함.
    wattron(win, COLOR_PAIR(CP_HEAD)); // HEAD 색
    mvwprintw(win, snakeData[0][0], snakeData[0][1] * 2, "\u25CF");
    wattroff(win, COLOR_PAIR(CP_HEAD));
    
    for (int i = 1; i < snakeData.size(); i++)
    {
        // snake의 Body를 그려주기 전에 snake가 지나간 자국들을 배경 색으로 칠해서 지움.
        // 그렇지 않으면 background를 칠해줘도 snake가 지나간 자국이 남음.
        wattron(win, COLOR_PAIR(CP_BKGR));
        mvwprintw(win, snakeData[i][0], snakeData[i][1] * 2, " ");
        mvwprintw(win, snakeData[i][0], snakeData[i][1] * 2 + 1, " ");
        wattroff(win, COLOR_PAIR(CP_BKGR));
        
        // snake의 Body 칠해주기
        // 비 아스키 문자를 출력하면 screen 상에 두 칸을 차지하므로 가로를 두 배로 늘려서 특수문자 출력함.
        wattron(win, COLOR_PAIR(CP_BODY)); // BODY 색
        mvwprintw(win, snakeData[i][0], snakeData[i][1] * 2, "\u25CF");
        wattroff(win, COLOR_PAIR(CP_BODY));
    }
}

Gate Snake::getGate1(){
    return Gate1;
}
Gate Snake::getGate2(){
    return Gate2;
}
void Snake::setGate1(int x,int y){
    Gate1.x = x;
    Gate1.y = y;
}
void Snake::setGate2(int x,int y){
    Gate2.x =x;
    Gate2.y =y;
}

int Snake::snakelength(){
    return snakeData.size();
}

bool Snake::getGatepass(){
    return Gatepass;
}

void Snake::setGatePass(bool a){
    Gatepass = a;
}

Gate Snake::RandomGate(vector<vector<int>> &mapData,int a,int b)
{
        Gate NextGate;
        srand((unsigned int)time(0));
        while(true)
        {
            NextGate.x = rand()%21;
            NextGate.y = rand()%21;
            if (mapData[NextGate.x][NextGate.y]==1 && NextGate.x !=a && NextGate.y !=b)
            {
                break;
            }
        }
        return NextGate; 
    }