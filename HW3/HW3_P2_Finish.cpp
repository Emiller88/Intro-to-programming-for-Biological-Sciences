// Homework 3 Problem 2
// Edmund Miller
// Takes two numbers from the user and returns the greatest common divisor

#include <iostream>

int gcd(int x, int y);

using namespace std;

int main() {
  int x, y;
  do {
    cout << "First Number: ";
    cin >> x;
    cout << "Second Number: ";
    cin >> y;
    // Check if x > y
    if (y > x) {
      cout << "Invalid input please make x > y" << endl;
    }
  } while (y > x);

  cout << "GCD: " << gcd(x, y) << endl;

  return 0;
}

int gcd(int x, int y) {
  if (x == 0) {
    return y;
  }
  if (y == 0) {
    return x;
  }
  if (x == y) {
    return y;
  } else {
    return gcd(y, x % y);
  }
}
