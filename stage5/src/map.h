#include <vector>
#include <ncurses.h>

using std::vector;

class Map
{
    // map 객체의 실제 데이터
    vector<vector<int>> mapDatum;

public:
    // 각 stage별 mapData들의 집합
    static vector<vector<int>> mapData[];
    static int current_map_index;

    static Map bgMap;
    static void setbgMap(const vector<vector<int>> &inputMapData);

    // mapData의 row size 반환
    int getRowSize();

    // mapData의 column size 반환
    int getColSize();
    vector<int> &operator[](int idx);

    // Map 보여주기
    void display(WINDOW *win);
};
