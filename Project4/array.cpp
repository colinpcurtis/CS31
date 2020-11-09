#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <cassert>
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
     int runningMax;  // position of max
     string maxElement; // max element to compare with
     if (n <= -1) {
          return -1;
     }

     maxElement = a[0]; // compare with this element during loop
     runningMax = -1; // initialize to something we can't get while looping
     // ensures we return -1 if no interesting elements

     for (int i = 0; i < n; i++) {
          if ( a[i] > maxElement ) { // compares elements alphabetically
               maxElement = a[i]; // reset maxElement and position where it occurs
               runningMax = i;   
          }
     }
     return runningMax;
}


int rotateLeft(string a[], int n, int pos) {
     if (n <= -1 || pos <= -1) { // access out of range element
          return -1;
     }

     string toLast = a[pos];
     for (int i = pos + 1; i < n; i++) { // modify the array inplace by shifting elements to the left
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
     int upper = n / 2 - 1; // upper loop limit

     int i = 0;
     int j;
     while (i <= upper ) { // go through array and swap low and high elements
          j = n - i - 1; // upper element for swapping
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
     // double check less than or equal
     for (int i = 0; i <= n1 - n2; i++) { // loop to n1 - n2 since the last possible match is at that position, ensures no out of range errors
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
                    return i; // return position in first array
               }
          }
     }
     return -1;
} 


int divide(string a[], int n, string divider) {
     if (n <= -1) {
          return -1;
     }
     // easiest approach is to alphabetically sort the array since it puts the 
     // array in a usable and reproducable order each time the function is called
     for (int i = 0; i < n - 1; i++) {
          for (int j = 0; j < n - 1; j++ ) {
               if ( a[j + 1] < a[j] ) { // if left element is greater than right element, swap them
                    string temp = a[j + 1];
                    a[j + 1] = a[j];
                    a[j] = temp;
               } 
          }
     }
     // traverse array and return first index whose element is less than or equal to the divider
     for (int i = 0; i < n - 1; i++) {
          if (divider <= a[i] ) {
               return i;
          }
     }
     return n; // return n if no matches
}
 
int main() {
     // string candidate[6] = { "jamie", "lindsey", "mark", "susan", "joe", "donald" };
     // // string candidate2[4] = { "mark", "sara", "lindsey", "mike" };
     // int x = divide(candidate, 6, "kamala");
     
     // for (int i = 0; i < 6; i++) {
     //      cout << candidate[i] << endl;;
     // }
     // cout << "return: " << x << endl;
          string h[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
          assert(lookup(h, 7, "kamala") == 5);
	    assert(lookup(h, 7, "joe") == 2);
	    assert(lookup(h, 2, "joe") == -1);
	    assert(positionOfMax(h, 7) == 3);

	    string g[4] = { "martha", "mark", "lindsey", "sara" };
         
	    assert(differ(h, 4, g, 4) == 2);
	    assert(appendToAll(g, 4, "?") == 4 && g[0] == "martha?" && g[3] == "sara?");
	    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "mark?");

	    string e[4] = { "joe", "susan", "", "kamala" };

	    assert(subsequence(h, 7, e, 4) == 2);

         assert(positionOfMax(h, 0) == -1);
         assert(lookup(e, 4, "donald") == -1);
         assert(rotateLeft(e, 4, 0) == 0);
         assert(differ(e, 0, h, 7) == 0);
         assert(differ(e, 4, e, 4) == 4);

	    string d[5] = { "mark", "mark", "mark", "susan", "susan" };
	    assert(countRuns(d, 5) == 2);
	
	    string f[3] = { "lindsey", "joe", "mike" };
	    assert(lookupAny(h, 7, f, 3) == 2);

	    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");
	
	    assert(divide(h, 7, "lindsey") == 3);

         string n[4] = { "martha", "mark", "lindsey", "sara" };

         assert(flip(n, 4) == 4 && n[0] == "sara" && n[1] == "lindsey" && n[2] == "mark" && n[3] == "martha");

	
	    cout << "All tests succeeded" << endl;
     
}