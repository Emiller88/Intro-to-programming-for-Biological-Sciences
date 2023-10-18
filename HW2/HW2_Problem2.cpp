// HW 2 Problem 2
// Edmund Miller
// Compares two base pair sequences and returns the sequence identity

// Advice for the young researcher

#include <cmath>
#include <iostream>

using namespace std;

char getInput(bool &);
void checkInput(char, bool &);
void compareSeqs(char, char, float &);
float calculateSim(float, float);
void outputValue(float);

int main() {
  // Variables
  char sq1c1, sq1c2, sq1c3, sq1c4, sq1c5, sq1c6, sq1c7, sq1c8, sq1c9, sq1c10;
  char sq2c1, sq2c2, sq2c3, sq2c4, sq2c5, sq2c6, sq2c7, sq2c8, sq2c9, sq2c10;
  float length = 10;
  float simBpCount = 0;
  float iD12 = 0;
  bool badData = true;
  char yesOrNo = true;

  do {

    do {
      cout << "Input Sequence 1:" << endl;

      badData = true;

      // Get first sequence input
      sq1c1 = getInput(badData);
      sq1c2 = getInput(badData);
      sq1c3 = getInput(badData);
      sq1c4 = getInput(badData);
      sq1c5 = getInput(badData);
      sq1c6 = getInput(badData);
      sq1c7 = getInput(badData);
      sq1c8 = getInput(badData);
      sq1c9 = getInput(badData);
      sq1c10 = getInput(badData);
    } while (badData == false);

    do {
      cout << "Input Sequence 2:" << endl;

      badData = true;

      // Get Second Sequence Input
      sq2c1 = getInput(badData);
      sq2c2 = getInput(badData);
      sq2c3 = getInput(badData);
      sq2c4 = getInput(badData);
      sq2c5 = getInput(badData);
      sq2c6 = getInput(badData);
      sq2c7 = getInput(badData);
      sq2c8 = getInput(badData);
      sq2c9 = getInput(badData);
      sq2c10 = getInput(badData);
    } while (badData == false);

    // In case more sequences are desired
    simBpCount = 0;

    // Compare Sequences
    compareSeqs(sq1c1, sq2c1, simBpCount);
    compareSeqs(sq1c2, sq2c2, simBpCount);
    compareSeqs(sq1c3, sq2c3, simBpCount);
    compareSeqs(sq1c4, sq2c4, simBpCount);
    compareSeqs(sq1c5, sq2c5, simBpCount);
    compareSeqs(sq1c6, sq2c6, simBpCount);
    compareSeqs(sq1c7, sq2c7, simBpCount);
    compareSeqs(sq1c8, sq2c8, simBpCount);
    compareSeqs(sq1c9, sq2c9, simBpCount);
    compareSeqs(sq1c10, sq2c10, simBpCount);

    iD12 = calculateSim(simBpCount, length);

    outputValue(iD12);

    do {
      cout << "Would you like to enter new sequences? type 'y' for yes and 'n' "
              "for no"
           << endl;
      cin >> yesOrNo;
    } while (yesOrNo != 'y' && yesOrNo != 'n');

  } while (yesOrNo == 'y');

  cout << "Program Finished, have a good day!" << endl;
}

char getInput(bool &dataValid) {
  char seqBP = 'Z';

  cin >> seqBP;
  seqBP = toupper(seqBP);
  checkInput(seqBP, dataValid);

  return seqBP;
}

void checkInput(char seqBP, bool &dataValid) {
  // Check for correct letters in array

  if (seqBP != 'A' && seqBP != 'T' && seqBP != 'G' && seqBP != 'C' &&
      seqBP != 'U') {
    cout << "Please input only 'ATGCU'" << endl;
    dataValid = false;
    return;
  }
}

void compareSeqs(char seq1BP, char seq2BP, float &simBpCount) {
  if (seq1BP == seq2BP) {
    simBpCount++;
  }
}

float calculateSim(float simBP, float length) { return (simBP / length); }

void outputValue(float iD12) {
  cout << "The sequence identity between sequence 1 and 2 is:" << endl
       << iD12 << endl;
}
