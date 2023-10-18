#include <curses.h>
#include <stdio.h>

int main() {
  char resp;
  int i, j, y, x;
  int width, height;

  initscr();
  getmaxyx(stdscr, height, width);
  clear();

  box(stdscr, '*', '-');
  move(1, 2); // goto row 1 column 2
  printw("Print BIG letters");
  move(1, width - 10);
  printw("10/13/16");
  /* send stdscr to terminal  */
  refresh();

  cbreak(); // make characters immediately accessible
  noecho(); // don't echo inputs

  move(height - 2, 2);
  printw("Hit any key to see what happens next:  ");
  getyx(stdscr, y, x);
  move(y, x - 2);

  refresh();
  resp = getch();
  // draw big H
  for (i = 3; i < 22; i++) {
    move(i, 15);
    printw("Hello");
    move(i, 35);
    printw("Hello");
    if ((10 < i) && (i < 14)) {
      move(i, 20);
      for (j = 20; j < 35; j += 5)
        printw("Hello");
    }
  }
  refresh();

  move(height - 2, 2);
  printw("Hit any key to see what happens next:  ");
  getyx(stdscr, y, x);
  move(y, x - 2);
  refresh();
  resp = getch();

  // draw big i
  for (i = 3; i < 22; i++) {
    move(i, 55);
    printw("Hello");
    if (((3 <= i) && (i <= 5)) || ((19 <= i) && (i <= 21))) {
      move(i, 50);
      for (j = 50; j < 65; j += 5)
        printw("Hello");
    }
  }

  move(height - 2, 2);
  printw("Hit any key to exit:                   ");
  move(height - 2, 22);
  resp = getch();

  endwin();

  return 0;
}
