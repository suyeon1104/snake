#include <deque>
#include <vector>
#include <ncurses.h>
using namespace std;


// Snake 클래스
class Snake
{
    enum Direction {
        LEFT, RIGHT, UP, DOWN
    };
    Direction dir;
    bool Fail = false;
    deque<vector<int>> snakeData = deque<vector<int>>();
    int key;
public:
    Snake(vector<vector<int>> mapData, WINDOW* win);
    void findBody(vector<vector<int>> &mapData);
    
    void tick();

    bool getFail();
    void display(WINDOW *win);
};