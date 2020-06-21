#include <vector>
#include <ncurses.h>

using std::vector;

class Map
{   
    
    
    // map 객체의 실제 데이터
    vector<vector<int>> mapData;
    
public:
    Map();
    
    // 각 stage별 mapData들의 집합
    static vector<vector<int>> mapDatas[];
    
    static Map bgMap;
    static void setbgMap(const vector<vector<int>> &inputMapData);
    static void setbgMapraw(const vector<vector<int>> &inputMapData);
    static void setbgMapgate(const vector<vector<int>> &inputMapData,int x1,int y1,int x2,int y2);

    // mapData의 row size 반환
    int getRowSize();

    // mapData의 column size 반환
    int getColSize();


    vector<int>& operator[](int idx);

    // Map 보여주기
    void display(WINDOW *win);

    //Gate
};