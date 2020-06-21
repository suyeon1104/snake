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

    // 바탕, Wall과 ImmuneWall들만 저장하는 맵 데이터
    static Map bgMap;
    
    //bgMap 설정
    static void setbgMap(const vector<vector<int>> &inputMapData);
    static void setbgMapraw(const vector<vector<int>> &inputMapData);
    static void setbgMapgate(const vector<vector<int>> &inputMapData,int x1,int y1,int x2,int y2);

    // mapData의 row size 반환
    int getRowSize();

    // mapData의 column size 반환
    int getColSize();

    // Map 객체에서 직접 현재 맵의 인덱스 번째의 한 행에 대한 레퍼런스를 반환
    vector<int> &operator[](int idx);

    // 맵을 화면에 출력
    void display(WINDOW *win);
};
