void draw_board(Snake snake)
{
  // score board
  const int HEIGHT = Map::bgMap.getRowSize() / 2;
  const int WIDTH = 15;
  WINDOW *win2 = newwin(HEIGHT, WIDTH, WINDOW_MARGIN, Map::bgMap.getColSize() * 2 + WINDOW_MARGIN);
  wbkgd(win2, COLOR_PAIR(CP_BKGR));
  wattron(win2, COLOR_PAIR(CP_SCORE));
  mvwprintw(win2, 1, 1, "Score Board");
  mvwprintw(win2, 2, 1, ("B: " + to_string(snake.length) + " / " + to_string(snake.MAX_LENGTH)).c_str());
  mvwprintw(win2, 3, 1, ("+: " + to_string(snake.acquired_item_count)).c_str());
  mvwprintw(win2, 4, 1, ("-: " + to_string(snake.acquired_poison_count)).c_str());
  mvwprintw(win2, 5, 1, ("G: " + to_string(snake.passed_gate_count)).c_str());

  wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');
  wattroff(win2, COLOR_PAIR(CP_SCORE));
  wrefresh(win2);

  // mission board
  WINDOW *win3 = newwin(HEIGHT, WIDTH, WINDOW_MARGIN + HEIGHT, Map::bgMap.getColSize() * 2 + WINDOW_MARGIN);
  wbkgd(win3, COLOR_PAIR(CP_BKGR));
  wattron(win3, COLOR_PAIR(CP_MISSION));
  mvwprintw(win3, 1, 1, "Mission");
  mvwprintw(win3, 2, 1, ("B: " + to_string(0)).c_str());
  mvwprintw(win3, 3, 1, ("+: " + to_string(0)).c_str());
  mvwprintw(win3, 4, 1, ("-: " + to_string(0)).c_str());
  mvwprintw(win3, 5, 1, ("G: " + to_string(0)).c_str());

  wborder(win3, '|', '|', '-', '-', '+', '+', '+', '+');
  wattroff(win3, COLOR_PAIR(CP_MISSION));
  wrefresh(win3);
}
