#include <cmath>
#include <curses.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
  ifstream seqfile;
  int seqLength = 0;
  double count = 0, NT_c[4][10] = {{0}, {0}, {0}, {0}}, I[10] = {0},
         H[10] = {0};
  double sites[10];
  string line, filename;

  cout << "Input file name: " << endl;
  getline(cin, filename);

  // Read data from file and compute frequencies
  seqfile.open(filename.c_str());
  while (getline(seqfile, line)) {
    seqLength = line.length();
    for (int i = 0; i < seqLength; i++) {
      if (line.substr(i, 1) == "A" || line.substr(i, 1) == "a")
        NT_c[0][i]++;
      else if (line.substr(i, 1) == "G" || line.substr(i, 1) == "g")
        NT_c[1][i]++;
      else if (line.substr(i, 1) == "C" || line.substr(i, 1) == "c")
        NT_c[2][i]++;
      else if (line.substr(i, 1) == "U" || line.substr(i, 1) == "u")
        NT_c[3][i]++;
      else if (line.substr(i, 1) == "-")
        ;
      else
        cout << "Error in the input sequence" << endl;
    }
    count++;
  }

  // Compute Entropy and Information metrics
  for (int j = 0; j < seqLength; j++) {
    for (int z = 0; z < 4; z++) {
      if (NT_c[z][j] > 0)
        H[j] -= (NT_c[z][j] / count) * log(NT_c[z][j] / count) / log(2);
    }
    if (NT_c[0][j] + NT_c[1][j] + NT_c[2][j] + NT_c[3][j] == 0)
      I[j] = 0;
    else
      I[j] = 2 - H[j];
  }

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
}
