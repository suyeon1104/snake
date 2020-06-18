#include <vector>
#include <ncurses.h>

using std::vector;

class Map
{
    vector<vector<int>> mapData;
public:
    static Map bgMap;
    static void setbgMap(const vector<vector<int>> &inputMapData);
    int getRowSize();
    int getColSize();
    void display(WINDOW *win);
};