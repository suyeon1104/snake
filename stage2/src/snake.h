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
    deque<vector<int>> snakeData = deque<vector<int>>();
    int key;
public:
    Snake(vector<vector<int>> mapData);
    void findBody(vector<vector<int>> &mapData);
    
    void tick();
    void checkWallConflict(int, int);
    void checkBodyConflict(int headR, int headC);
    void display(WINDOW *win);
};