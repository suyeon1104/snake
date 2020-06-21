#include <deque>
#include <vector>
#include <ncurses.h>

using namespace std;

typedef struct _Gate
    {
        int x;
        int y;
    }Gate;


// Snake 클래스
class Snake
{
    // snake의 이동 방향 열거형 상수
    enum Direction {
        LEFT, RIGHT, UP, DOWN
    };

    // snake의 현재 이동 방향
    Direction dir;
    
    // snake의 map 상의 좌표를 나타내는 snakeData를 int의 vector의 deque로 선언
    // deque로 선언하여 vector에서는 사용 불가능한 push_front() 메소드 사용 가능하게 함
    deque<vector<int>> snakeData = deque<vector<int>>();
    
    // 매 tick마다 입력받는 현재 키. 입력이 없으면 -1 값을 가짐.
    int key;

    //gate
    int gatetry = -10;
    int gatesnakebody = -1;

public:

    bool Gatepass = true;
    
    // Snake의 생성자로서, mapData를 이용하여 snake의 위치 정보와 초기 방향을 검출하고 이를 적용한 Snake의 객체를 생성함.
    Snake(vector<vector<int>> mapData);

    // mapData로부터 snake의 body를 재귀적으로 찾아내기
    void findBody(vector<vector<int>> &mapData);
    
    // 한 tick 내에 수행하는 snake의 동작 정의
    void tick(vector<vector<int>> mapData);
    
    // 새 Head 위치좌표(headR, headC)가 Wall과 겹칠 경우 Failure Exception을 throw함.
    void checkWallConflict(int headR, int headC);
    
    // 새 Head 위치좌표(headR, headC)가 이동한 Body 위치좌표와 겹칠 경우 Failure Exception을 throw함.
    void checkBodyConflict(int headR, int headC);

    // 새 Head 위치좌표(headR, headC)가 Gate와 만날경우 다른 Gate로 head의 방향을 알 맞게 조절함.
    Gate checkGatein(int headR, int headC,vector<vector<int>> &mapData);

    // snake를 화면에 표시
    void display(WINDOW *win);

    //map중 게이트의 위치데이터
    Gate Gate1;
    Gate Gate2;

    // Gate1 반환
    Gate getGate1();

    // Gate2 반환
    Gate getGate2();
    
    //Gate1 설정
    void setGate1(int x,int y);

    //Gate2 설정
    void setGate2(int x,int y);

    //gate random
    Gate RandomGate(vector<vector<int>> &mapData,int a , int b);
    

    int snakelength();
    
    bool getGatepass();

    void setGatePass(bool a);
};