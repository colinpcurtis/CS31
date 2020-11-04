#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
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
          if(a[i] == value) { // check array element is equal to the compared value
               return i; // return position
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

     maxElement = a[0]; // compare with this element during loop
     runningMax = -1; // initialize to something we can't get while looping
     for (int i = 0; i < n; i++) {
          if (a[i].compare(maxElement) > 0) { // compares elements alphabetically
               maxElement = a[i]; // reset maxElement and position where it occurs
               runningMax = i;   
          }
     }
     cerr << maxElement << endl;
     return runningMax;
}


int rotateLeft(string a[], int n, int pos) {
     if (n <= -1) {
          return -1;
     }

     string toLast = a[pos];
     for (int i = pos + 1; i < n; i++) { // modify the array inplace
          // string intermediate = a[i];
          a[i - 1] = a[i]; 
     }
     a[n - 1] = toLast; // position that we rotate around is placed last
     return pos;
}


int countRuns(const string a[], int n) {
     if (n <= -1) {
          return -1;
     }

     int count = 1; // when we compare with the first element we already have a length 1 run
     string previousTerm = a[0]; // start comparing with the first position
     for (int i = 0; i < n; i++) {
          if (a[i] != previousTerm) { // if the current term in the sequence is not the previous term, then we add 1 to run
               previousTerm = a[i];
               count++;
          } else if (a[i] == previousTerm) { // more than 1 consecutive element
               continue; 
          }
     }
     return count;
}

int flip(string a[], int n) {
     if (n <= -1) {
          return -1;
     }

     int i = 0;
     int j;
     while (i < n / 2) { // go through array and swap low and high elements
          j = n - i - 1; // upper comparison for what to swap
          string temp = a[i]; // use temp to swap variable positions
          a[i] = a[j];
          a[j] = temp;
          i++;
     }
     return n;
}


int differ(string a1[], int n1, string a2[], int n2) {
     if (n1 <= -1 || n2 <= -1) {
          return -1;
     }

     int min_length = min(n1, n2); // only loop to minimum length so we have no out of range errors
     for (int i = 0; i <= min_length; i++) {
          if (a1[i] != a2[i]) { // check if corresponding elements are different, return position
               return i; 
          }
     } 
     return min_length; // return minimum of lengths if they're equal at the end of looping
}


int subsequence(const string a1[], int n1, const string a2[], int n2) {
     if (n1 <= -1 || n2 <= -1) {
          return -1;
     }

     for (int i = 0; i < n1 - n2; i++) { // loop to n1 - n2 since the last possible match is at that position, ensures no out of range errors
          int numEqual = 0;
          for (int j = 0; j < n2; j++) {
               if (a1[i + j] == a2[j]) { // check corresponding positions in both arrays
                    numEqual++;
               }
          }
          if (numEqual == n2) { // if all positions match return the position in the main array
               return i;
          } 
     }
     return -1;
}


int lookupAny(const string a1[], int n1, const string a2[], int n2) {
     if (n1 <= -1 || n2 <= -1) {
          return -1;
     }

     for (int i = 0; i < n1; i++) { // upper bound is number of significant elements to consider
          for (int j = 0; j < n2; j++) {
               if (a1[i] == a2[j]) { // check if element in a1 matches any element in a2
                    return i;
               }
          }
     }
     return -1;
} 
 
int main() {
     string names[10] = { "kamala", "mark", "sara", "martha", "donald", "lindsey" };
     string set1[10] = { "jamie", "donald", "martha", "mark" };

     cout << lookupAny(names, 6, set1, 4) << endl;
     cout << lookupAny(names, 6, set1, 2) << endl;
     // for (int i = 0; i < 7; i++) {
     //      cout << d[i] << endl;;
     // }
     
}