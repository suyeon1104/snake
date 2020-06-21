#include "map.h"
#include "snake.h"
#include "main.h"



// 배경 맵 클래스
Map::Map(){
    
}
// 바탕, Wall과 ImmuneWall들만 저장하는 맵 데이터
Map Map::bgMap;

// 각 stage별 mapData를 저장하는 배열
vector<vector<int>> Map::mapDatas[] = {
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
        {1, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 1},
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

//bgMap 설정
void Map::setbgMap(const vector<vector<int>> &inputMapData) {
    bgMap.mapData = inputMapData;
    int nrow = bgMap.mapData.size();
    int ncol = bgMap.mapData[0].size();
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            // 7을 gate의 조건으로 설정
            if (bgMap.mapData[i][j] != 0 && bgMap.mapData[i][j] != 1 && bgMap.mapData[i][j] != 2 && bgMap.mapData[i][j] != 7) {
                bgMap.mapData[i][j] = 0;
            }
        }
    }
}
void Map::setbgMapraw(const vector<vector<int>> &inputMapData) {
    bgMap.mapData = inputMapData;
    int nrow = bgMap.mapData.size();
    int ncol = bgMap.mapData[0].size();
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            // 7을 gate의 조건으로 설정
            if (bgMap.mapData[i][j] != 0 && bgMap.mapData[i][j] != 1 && bgMap.mapData[i][j] != 2) {
                bgMap.mapData[i][j] = 0;
            }
        }
    }
}
void Map::setbgMapgate(const vector<vector<int>> &inputMapData,int x1,int y1,int x2, int y2) {
    bgMap.mapData = inputMapData;
    int nrow = bgMap.mapData.size();
    int ncol = bgMap.mapData[0].size();
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            // 7을 gate의 조건으로 설정
            if (bgMap.mapData[i][j] != 0 && bgMap.mapData[i][j] != 1 && bgMap.mapData[i][j] != 2 && bgMap.mapData[i][j] != 7) {
                bgMap.mapData[i][j] = 0;
            }
        }
    }
    bgMap.mapData[x1][y1] = 7;
    bgMap.mapData[x2][y2] = 7;

}


// mapData의 행 수 반환
int Map::getRowSize()
{
    return mapData.size();
}

// mapData의 열 수 반환
int Map::getColSize()
{
    return mapData[0].size();
}


// map 객체에서 인덱스 연산자를 이용해 직접 mapData에 접근하도록 만듦
vector<int>& Map::operator[](int idx) {
    return mapData[idx];
}

// Map 객체의 mapData를 이용해 맵 보여주기
void Map::display(WINDOW *win)
{
    int nrow = mapData.size();
    int ncol = mapData[0].size();
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            if (mapData[i][j] == 0)
            {
                // 공백이 아닌 다른 문자로 print 해줘야 snake 흔적을 지워줌.
                wattron(win, COLOR_PAIR(CP_BKGR));
                mvwprintw(win, i, j * 2, "M");
                mvwprintw(win, i, j * 2 + 1, "M");
                wattroff(win, COLOR_PAIR(CP_BKGR));
            }
            else if (mapData[i][j] == 1)
            {
                wattron(win, COLOR_PAIR(CP_WALL));
                mvwprintw(win, i, j * 2, "\u25A0");
                wattroff(win, COLOR_PAIR(CP_WALL));
            }
            else if (mapData[i][j] == 2)
            {
                wattron(win, COLOR_PAIR(CP_IMMUNE_WALL));
                mvwprintw(win, i, j * 2, "\u25A0");
                wattroff(win, COLOR_PAIR(CP_IMMUNE_WALL));
            }
            else if (mapData[i][j] == 7)
            {
                wattron(win, COLOR_PAIR(CP_GATE));
                mvwprintw(win, i, j * 2, "\u25A0");
                wattroff(win, COLOR_PAIR(CP_GATE));
            }
        }
    }
    wrefresh(win);
}