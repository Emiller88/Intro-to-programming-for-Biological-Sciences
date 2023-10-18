// Edmund Miller
// HW5 - Fasta File Reader
// This program reads a fasta file and returns the desired seq to the user

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getFile(string &);
void readFile(fstream &, vector<vector<string>> &, int &);
void outputSeq(int, int, vector<vector<string>>);

int main() {
  // Create variables
  vector<vector<string>> tRNA_vec;
  string fileName;
  fstream inFile;
  int userNum;
  int seqCount = 0;

  getFile(fileName);
  inFile.open(fileName.c_str());
  if (!inFile) // If the file does not open correctly return an error.
  {
    cout << "Error openning file." << endl;
    return 1;
  }
  readFile(inFile, tRNA_vec, seqCount);

  cout << "Select sequence number" << endl; // asks for user to input a sequence
  cin >> userNum;
  userNum--; // Corrects userNum to work with vector numbering
  if (userNum < 0 ||
      userNum >= tRNA_vec.size()) // Check to make sure users number is valid
  {
    cout << "Sequence number outside of range." << endl;
    return 1;
  }

  outputSeq(userNum, seqCount, tRNA_vec);

  return 0;
}

// Function to get Fasta file name desired for use from user
void getFile(string &fileName) {
  cout << "Input Fasta file name:" << endl;
  cin >> fileName;
}

// Reads through file and stores in a vector of Name and Sequence to then be
// stored in a large vector of vectors
void readFile(fstream &inFile, vector<vector<string>> &tRNA_vec,
              int &seqCount) {
  vector<string> fileVec; // vector to push into vector of vectors
  string fileInput;       // string to get input from
  int seqLength = -1;

  while (!inFile.eof()) {
    getline(inFile, fileInput);
    if (fileInput[0] != '>') // Skips lines that don't start with a description
    {
      continue;
    }

    fileVec.push_back(fileInput);
    getline(inFile, fileInput);
    if (seqLength == -1)
      seqLength = fileInput.length();
    else if (fileInput.length() !=
             seqLength) // Checks to see if the current sequence matches the
                        // first sequence length
    {
      cout << "Error in sequence " << (seqCount + 1) << "(" << fileVec[0]
           << "):  sequences must be of same length" << endl;
      exit(0);
    }
    fileVec.push_back(fileInput);
    tRNA_vec.push_back(fileVec); // Puts vector in vector of vectors
    fileVec.clear();             // clears input vector
    seqCount++;
  }
}

void outputSeq(int userNum, int seqCount, vector<vector<string>> tRNA_vec) {
  cout << "The name of your molecule is:" << endl
       << tRNA_vec[userNum][0] << endl
       << "The Sequence of you molecule is:" << endl
       << tRNA_vec[userNum][1] << endl
       << "The length of your sequence is:" << endl
       << tRNA_vec[userNum][1].length() << endl
       << "There are a total of " << tRNA_vec.size()
       << " sequences in your alignment" << endl;
}