#include <vector>
#include <ncurses.h>

using std::vector;

class Map
{
    vector<vector<int>> mapData;
public:
    static vector<vector<int>> mapDatas[];
    static Map bgMap;
    static void setbgMap(const vector<vector<int>> &inputMapData);

    int getRowSize();
    int getColSize();
    vector<int>& operator[](int idx);
    void display(WINDOW *win);
};