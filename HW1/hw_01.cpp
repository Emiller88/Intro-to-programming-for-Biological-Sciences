// HW 1 Problem 2
// Edmund Miller
// Calculates either the bp distance or Recombination fration based on user's
// choice

#include <cmath>
#include <iostream>

using namespace std;

int main() {
  // Declare user input variables
  int disOrFrac = 0;
  float userVal = 0;
  float desiredVal = 0;

  do {
    cout << "1. Distance" << endl
         << "2. Recombination Fraction" << endl
         << "Enter the number before the value you would like to compute: "
         << endl;

    cin >> disOrFrac;

    // Check user input and return if correct.
    if (disOrFrac != 1 && disOrFrac != 2) {
      cout << "Error, please enter 1 or 2" << endl; // Error Message
    }

  } while (disOrFrac != 1 && disOrFrac != 2); // Repeat if invalid input

  if (disOrFrac == 1) // User wants the Distance
  {
    do {
      cout << "Please input the Recombination Fraction(ex: 0.50): ";
      cin >> userVal;
      if (userVal > 0.5 || userVal <= 0) {
        cout << "Please input a value less than or equal to 0.5 and greater "
                "than 0"
             << endl;
      }
    } while (userVal > 0.5 || userVal < 0);

    desiredVal = 50 * log10(1 / (1 - (2 * userVal))); // Calculate the Distance

    cout << "The value for dAB is: " << desiredVal << "centi-Morgan" << endl
         << endl;
  }

  else if (disOrFrac == 2) // User wants recombination fraction
  {
    do {
      cout << "Please input the Base pair distance in cM: ";
      cin >> userVal;
      if (userVal > 3000 || userVal < 0) {
        cout << "Please input a value between 3000 and 0." << endl;
      }
    } while (userVal > 3000 || userVal < 0);

    desiredVal =
        (((1 / pow(10, userVal / 50)) - 1) / -2); // Calc recombination factor

    cout << "The value for cAB is: " << desiredVal << endl
         << endl; // Output final value
  }

  else {
    return 1;
  }

  return 0;
}