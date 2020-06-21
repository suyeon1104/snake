#include <deque>
#include <vector>
#include <ncurses.h>

using namespace std;

//return 을 두개 하기위한 gate sturct
typedef struct _Gate
{
    int x;
    int y;
} Gate;

// Snake 클래스
class Snake
{
    // snake의 이동 방향 열거형 상수
    enum Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    // snake의 현재 이동 방향
    Direction dir;

    // snake의 map 상의 좌표를 나타내는 snakeData를 int의 vector의 deque로 선언
    // deque로 선언하여 vector에서는 사용 불가능한 push_front() 메소드 사용 가능하게 함
    deque<vector<int>> snakeData = deque<vector<int>>();

    // mapData로부터 snake의 body를 재귀적으로 찾아내기
    void findBody(vector<vector<int>> &mapData);

    // 새 Head 위치좌표(headR, headC)가 Wall과 겹칠 경우 Failure Exception을 throw함.
    void checkWallConflict(int headR, int headC);

    // 새 Head 위치좌표(headR, headC)가 이동한 Body 위치좌표와 겹칠 경우 Failure Exception을 throw함.
    void checkBodyConflict(int headR, int headC);

    //헤드나 바디가 gate에 있는지 검사
    Gate checkGatein(int headR, int headC);

    //snake gate를 빠져나갔는지 검사
    int gatetry = -10;
    //snake가 gate를 빠져나갔는지 검사하기위해 필요한 몸길이
    int gatesnakebody = -1;
    //gate를 지났는지 true,false로 표시
    bool Gatepass = true;

public:
    // Snake의 생성자로서, mapData를 이용하여 snake의 위치 정보와 초기 방향을 검출하고 이를 적용한 Snake의 객체를 생성함.
    Snake(vector<vector<int>> mapData);

    // 한 tick 내에 수행하는 snake의 동작 정의
    void tick();

    // snake를 화면에 표시
    void display(WINDOW *win);

    const int MAX_LENGTH = 10;
    const int MISION_ITEM_COUNT = 5;
    const int MISION_POSION_COUNT = 3;
    const int MISION_GATE_COUNT = 3;
    int length = 6;
    int acquired_item_count = 0;
    int acquired_poison_count = 0;
    int passed_gate_count = 0;

    //map중 게이트의 위치데이터
    Gate Gate1;
    Gate Gate2;

    // Gate1 반환
    Gate getGate1();

    // Gate2 반환
    Gate getGate2();

    //Gate1 설정
    void setGate1(int x, int y);

    //Gate2 설정
    void setGate2(int x, int y);

    //gate random 설정
    Gate RandomGate(vector<vector<int>> &mapData, int a, int b, int row, int col);

    //snake 길이
    int snakelength();
    //gatepass 받아오기
    bool getGatepass();

    //gatepass 설정
    void setGatePass(bool a);
};
