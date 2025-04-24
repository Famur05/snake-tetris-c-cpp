#include "frontend.h"

int main() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);

  int input = 0;
  while (1) {
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(1, 1, "Choose a Game:");
    attroff(COLOR_PAIR(1));
    mvprintw(3, 1, "1. Tetris");
    mvprintw(5, 1, "2. Snake");
    mvprintw(7, 1, "q. Quit");
    refresh();

    input = 0;
    while (input != '1' && input != '2' && input != 'q') {
      input = getch();
    }

    if (input == 'q') {
      break;
    }

    clear();
    refresh();

    if (input == '1') {
      tetris();
    } else if (input == '2') {
      snake();
    }
  }

  endwin();
  return 0;
}
