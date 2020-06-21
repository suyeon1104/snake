#include <string>
using namespace std;

// 컬러 팔레트 열거형 상수
enum Palette
{
    CP_BKGR = 1,    // 바탕 팔레트
    CP_WALL,        // 변(Wall) 팔레트
    CP_IMMUNE_WALL, // 모서리(Immune Wall) 팔레트
    CP_HEAD,        // Snake HEAD 팔레트
    CP_BODY,        // Snake BDOY 팔레트
    CP_GROWTH,      // GROWTH ITEM 팔레트
    CP_POISON,      // POISON ITEM 팔레트
    CP_GATE,        // GATE 팔레트
    CP_MESSAGE,     // MESSAGE 팔레트
    CP_SCORE,       // SCORE 팔레트
    CP_MISSION,     // MISSION 팔레트
};

// Game Over
class Failure
{
public:
    string message;
    Failure(const string& msg): message(msg) {
    }
};