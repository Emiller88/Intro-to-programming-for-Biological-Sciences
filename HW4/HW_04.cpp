// HW 4
// Edmund Miller
// Calculates Height from sequence file and outputs to file and a window using
// nCurses

#include <cmath>
#include <curses.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

void getFileInput(ifstream &, string, double &, double[4][10], int &);
void calcEntAndHeight(int, double, double[4][10], double[], double[],
                      double heights[4][5], string filename2);
void displayScreen(int seqLength, double heights[4][5]);
void displayA(double height, int x, int y);
void displayG(double height, int x, int y);
void displayC(double height, int x, int y);
void displayU(double height, int x, int y);

int main() {
  ifstream seqfile;
  int seqLength = 0;
  double count = 0, NT_c[4][10] = {{0}, {0}, {0}, {0}}, I[10] = {0},
         H[10] = {0}, heights[4][5];
  string line, filename, filename2;

  cout << "Input file name: " << endl;
  getline(cin, filename);

  cout << "Output file name: " << endl;
  getline(cin, filename2);

  getFileInput(seqfile, filename, count, NT_c,
               seqLength); // Get seq from inputfile

  calcEntAndHeight(seqLength, count, NT_c, H, I, heights, filename2);

  displayScreen(seqLength, heights);

  return 0;
}

/*
 * Read data from the file and compute frequencies
 */
void getFileInput(ifstream &seqfile, string filename, double &count,
                  double NT_c[4][10], int &seqLength) {
  seqfile.open(filename.c_str());
  string line;

  seqLength = 5; // Allowed to assume sequence is fixed to 5.

  while (getline(seqfile, line)) {
    // seqLength = line.length();
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
  seqfile.close();
}

/*
 * Compute Entropy and Information metrics and store the content Ii per site
 * and the heights for each of the RNA nucleotides in the sequence at position
 * 'i' in the output file.
 */
void calcEntAndHeight(int seqLength, double count, double NT_c[4][10],
                      double H[], double I[], double heights[4][5],
                      string filename2) {
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

  // Store Logo Information in text file
  FILE *outfile = fopen(filename2.c_str(), "w");

  for (int j = 0; j < seqLength; j++) {
    fprintf(outfile, "Information I[%d] = %f \n", j + 1, I[j]);
    fprintf(outfile, "Height of base A[%d] = %f \n", j + 1,
            I[j] * NT_c[0][j] / count);
    fprintf(outfile, "Height of base G[%d] = %f \n", j + 1,
            I[j] * NT_c[1][j] / count);
    fprintf(outfile, "Height of base C[%d] = %f \n", j + 1,
            I[j] * NT_c[2][j] / count);
    fprintf(outfile, "Height of base U[%d] = %f \n", j + 1,
            I[j] * NT_c[3][j] / count);
    fprintf(outfile, "-----------------------------------\n");
  }

  fclose(outfile);

  // Calculate letter heights for displaying
  for (int j = 0; j < seqLength; j++) {
    for (int i = 0; i < 4; i++) {
      heights[i][j] = 50 * (I[j] * NT_c[i][j] / count);
      heights[i][j] += 0.5;
      heights[i][j] = (long)heights[i][j];
    }

    cout << endl;
  }
}

/*
 * Calculate displayed letter height where largest displayed is a maximum of 20.
 */
int calcLetterHeight(double height) {
  int restrictedHeight;
  if (height > 20)
    restrictedHeight = 20;
  else
    restrictedHeight = (int)height;

  if (restrictedHeight > 1 && restrictedHeight < 18)
    restrictedHeight += 2;

  return restrictedHeight;
}

/*
 * Calculate the letter spacing including blank spaces for different sizes.
 */
int calcLetterSpacing(double height) {
  int letterHeight = calcLetterHeight(height);

  if (letterHeight == 1)
    letterHeight += 4;
  else
    letterHeight += 2;

  return letterHeight;
}

/*
 * Display the Letter A for a given height at row and column
 */
void displayA(double height, int row, int col) {
  if (height == 0)
    return;

  int letterHeight = calcLetterHeight(height);
  int letterWidth = letterHeight + 1;

  move(row, col);

  if (letterHeight == 1) {
    printw("A");
    return;
  }

  for (int i = 0; i < letterHeight; i++) {
    move(row - i, col);
    printw("A");

    // Handle the horizontal As as we go
    if ((letterHeight / 2 - 1) == i || i == letterHeight - 1) {
      for (int j = 0; j < letterWidth - 1; j++) {
        printw("A");
      }
    }

    move(row - i, col + letterWidth - 1);
    printw("A");
  }
}

/*
 * Display the Letter G for a given height at row and column
 */
void displayG(double height, int row, int col) {

  if (height == 0)
    return;

  int letterHeight = calcLetterHeight(height);
  int letterWidth = letterHeight + 1;

  move(row, col);

  if (letterHeight == 1) {
    printw("G");
    return;
  }

  for (int j = 0; j < letterWidth; j++) {
    printw("G");
  }

  for (int i = 1; i < letterHeight; i++) {
    move(row - i, col);
    printw("G");
  }

  move(row - letterHeight + 1, col);
  for (int j = 0; j < letterWidth; j++) {
    printw("G");
  }

  int middleBarRow = letterHeight / 2 - 1;

  for (int i = 1; i < letterHeight; i++) {
    if (i <= middleBarRow) {
      move(row - i, col + letterWidth - 1);
      printw("G");
    }
  }

  int middleBarWidth = letterWidth / 2 + 1;
  for (int i = 0; i < middleBarWidth; i++) {
    move(row - middleBarRow, col + i + (letterWidth - middleBarWidth));
    printw("G");
  }
}

/*
 * Display the Letter C for a given height at row and column
 */
void displayC(double height, int row, int col) {

  if (height == 0)
    return;

  int letterHeight = calcLetterHeight(height);
  int letterWidth = letterHeight + 1;

  move(row, col);

  if (letterHeight == 1) {
    printw("C");
    return;
  }

  for (int j = 0; j < letterWidth; j++) {
    printw("C");
  }

  for (int i = 1; i < letterHeight; i++) {
    move(row - i, col);
    printw("C");
  }

  move(row - letterHeight + 1, col);
  for (int j = 0; j < letterWidth; j++) {
    printw("C");
  }
}

/*
 * Display the Letter U for a given height at row and column
 */
void displayU(double height, int row, int col) {

  if (height == 0)
    return;

  int letterHeight = calcLetterHeight(height);
  int letterWidth = letterHeight + 1;

  move(row, col);

  if (letterHeight == 1) {
    printw("U");
    return;
  }

  for (int j = 0; j < letterWidth - 1; j++) {
    printw("U");
  }

  for (int i = 0; i < letterHeight; i++) {
    move(row - i, col);
    printw("U");

    move(row - i, col + letterWidth - 1);
    printw("U");
  }
}

/*
 * Display heights using ncurses
 */
void displayScreen(int seqLength, double heights[4][5]) {
  int width, height;

  initscr();
  getmaxyx(stdscr, height, width);
  clear();

  box(stdscr, '*', '-');
  refresh();

  cbreak(); // make characters immediately accessible
  noecho(); // don't echo inputs

  // Display the axis label
  string seqPosition = "SEQUENCE POSITION";
  move(height - 3, width / 2 - seqPosition.length() / 2);
  printw("SEQUENCE POSITION");

  // Blank margin space on either side
  int marginWidth = (width - 5 * 24) / 2;
  int labelRow = height - 4;
  int boxWidth = 25;

  // Display the sequence labels
  move(labelRow, marginWidth);
  printw("[           1          ]");
  move(labelRow, marginWidth + boxWidth);
  printw("[           2          ]");
  move(labelRow, marginWidth + 2 * boxWidth);
  printw("[           3          ]");
  move(labelRow, marginWidth + 3 * boxWidth);
  printw("[           4          ]");
  move(labelRow, marginWidth + 4 * boxWidth);
  printw("[           5          ]");

  // Display each scaled based on calculated height
  for (int j = 0; j < seqLength; j++) {
    displayA(heights[0][j], height - 5, marginWidth + j * boxWidth + 1);
    int lastHeight = calcLetterSpacing(heights[0][j]);

    displayG(heights[1][j], height - 5 - lastHeight,
             marginWidth + j * boxWidth + 1);
    lastHeight += calcLetterSpacing(heights[1][j]);

    displayC(heights[2][j], height - 5 - lastHeight,
             marginWidth + j * boxWidth + 1);
    lastHeight += calcLetterSpacing(heights[2][j]);

    displayU(heights[3][j], height - 5 - lastHeight,
             marginWidth + j * boxWidth + 1);
    lastHeight += calcLetterSpacing(heights[3][j]);
  }

  refresh();

  move(height - 2, 2);
  printw("Hit any key to exit:                   ");
  move(height - 2, 22);
  getch();

  endwin();
}
