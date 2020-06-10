#include <ncurses.h>
int main()
{
    initscr();                            // Curses 모드시작
    start_color();                        // Color 사용선언
    init_pair(1, COLOR_RED, COLOR_WHITE); // 색 attribute 설정
    
    attron(COLOR_PAIR(1));                // Attribute 적용
    printw("Hello world");                // Hello world 출력
    attroff(COLOR_PAIR(1));               // Attribute 해제
    
    refresh();                            // 실제 스크린에 출력
    getch();                              // 사용자입력대기
    endwin();                             // Curses 모드종료
    
    return 0;
}