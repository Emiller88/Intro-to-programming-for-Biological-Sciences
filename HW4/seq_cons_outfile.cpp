#include <cmath>
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
  char filename2[20];

  cout << "Input file name: " << endl;
  getline(cin, filename);

  cout << "Output file name: " << endl;
  cin >> filename2;

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

  FILE *outfile;

  // Store Logo Information in text file
  outfile = fopen(filename2, "w");

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
  return 0;
}
