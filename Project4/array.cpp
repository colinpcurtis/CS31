#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int appendToAll(string a[], int n, string value) {
     for (int i = 0; i < n; i++) {
          a[i] += value; 
     }
     return n;
}


int main() {
     string people[5] = { "donald", "joe", "mike", "lindsey", "kamala" };


     cout << appendToAll(people, 5, "!!!") << endl;
     cout << people << endl;
}