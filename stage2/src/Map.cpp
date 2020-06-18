#include "map.h"
#include "snake.h"
#include "main.h"

// 배경 맵 클래스

Map Map::bgMap;

void Map::setbgMap(const vector<vector<int>> &inputMapData) {
    bgMap.mapData = inputMapData;
    int nrow = bgMap.mapData.size();
    int ncol = bgMap.mapData[0].size();
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            if (bgMap.mapData[i][j] != 0 && bgMap.mapData[i][j] != 1 && bgMap.mapData[i][j] != 2) {
                bgMap.mapData[i][j] = 0;
            }
        }
    }
}

int Map::getRowSize()
{
    return mapData.size();
}
int Map::getColSize()
{
    return mapData[0].size();
}

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