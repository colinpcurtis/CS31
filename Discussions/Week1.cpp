#include <iostream>
#include <string>
using namespace std;

// int main() {
//      int x;
//      cout << x << endl; // didn't initialize variable but still got result 1.  Previously stored value in memory location
// }



// int main() {
//      cout << "what is your name? ";
//      string personName;
//      getline(cin, personName);

//      cout << "how old are you? ";
//      int age;
//      cin >> age;
//      cin.ignore(10000,'\n');
//      // fixes problem, throw away anything else on line, move to actual next line
//      // problem using getline after reading input
//      cout << "what is your quest? ";
//      string quest;
//      getline(cin, quest);

//      cout << "hello brave " << personName << "!" << endl;
//      cout << "you want " << quest << "." << endl;
//      cout << "if you live you will be " << age + 1 << " next year." << endl;
// }


int main() {
     // gather input data

     cout << "pay rate: ";
     double payRate;
     cin >> payRate;

     cout << "hours worked: ";
     double hoursWorked;
     cin >> hoursWorked;

     // compute and print earnings 

     double amountEarned = hoursWorked * payRate;
     double taxRate;
     cout.setf(ios::fixed);
     cout.precision(2);
     cout << "you earned " << amountEarned << endl;

     if(payRate >= 18) {
          taxRate = .1;
     } else {
          taxRate = .05; // value for taxRate will be well defined since it was initialized outside of if-else branching
     }
     cout << "$" << amountEarned * taxRate << " withheld" << endl;
    
}
