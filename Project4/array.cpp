#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int appendToAll(string a[], int n, string value) {
     if (n <= -1) {
          return -1;
     }
     for (int i = 0; i < n; i++) {
          a[i] += value; // add value to end of every string
     }
     return n;
}

int lookup(const string a[], int n, string value) {
     if (n <= -1) {
          return -1;
     }
     for (int i = 0; i < n; i++) {
          if(a[i] == value) { // return position in a where the elements match
               return i;
          }
     }
     return -1;
}

int positionOfMax(const string a[], int n) {
     int runningMax; 
     string maxElement;
     if (n <= -1) {
          return -1;
     }
     maxElement = a[0];
     runningMax = -1; // initialize to something we can't get while looping
     for (int i = 0; i < n; i++) {
          if (a[i].compare(maxElement) > 0) {
               maxElement = a[i];
               runningMax = i;
          }
     }
     cout << maxElement << endl;
     return runningMax;
}

int rotateLeft(string a[], int n, int pos) {
     string toLast = a[pos];
     for (int i = pos + 1; i < n; i++) {
          // string intermediate = a[i];
          a[i - 1] = a[i]; 
     }
     a[n - 1] = toLast;
     return pos;
}


int main() {
     string people[6] = { "donald", "joe", "mike", "lindsey", "susan", "kamala" };


     cout << rotateLeft(people, 5, 1) << endl;
     for (int i = 0; i < 5; i++) {
          cout << people[i] << endl;;
     }
}