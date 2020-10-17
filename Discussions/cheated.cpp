#include <iostream>
#include <string>
using namespace std;

int main() {
     int cheated;
     int score;

     cout << "Did the student cheat: ";
     cin >> cheated;
     cout << "What is the score: ";
     cin >> score;

     if (cheated == 1) {
          cout << "F" << endl;
     } else if (score > 80) {
          cout << "A" << endl;
     } else if (score > 70 && score <= 80) {
          cout << "B" << endl;
     } else if (score > 60 && score <= 70) {
          cout << "C" << endl;
     } else if (score <= 60) {
          cout << "F" << endl;
     }
}