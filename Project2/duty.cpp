#include <iostream>
#include <string>
using namespace std;

int main() {
     // initialize and declare variables
     double cheeseSpecificTax;
     string cheeseName;
     double importValue;
     string importerName;
     double importDuty = 0.0;  // we'll add onto this value

     cout << "Cheese type: ";
     getline(cin, cheeseName);

     cout << "Value: ";
     cin >> importValue;
     cin.ignore(1000, '\n'); // since we have an integer cin and a string getline directly after, we need to ignore characters upto newline

     cout << "Importer: ";
     getline(cin, importerName);

     // Check undefined cases
     if (cheeseName == "") {
          cout << "---" << endl;
          cout << "You must enter a cheese type";
     } else if (importValue <= 0) { // make sure if we want equal case
          cout << "---" << endl;
          cout << "The value must be positive";
     } else if (importerName == "") {
          cout << "---" << endl;
          cout << "You must enter an importer";
     } else {

          // find second step import tax amount 
          if (cheeseName == "cheshire" || cheeseName == "stilton"){
               cheeseSpecificTax = 0.014;
          } else {
               cheeseSpecificTax = 0.02;
          }

          // calculate import duty 
          if (importValue - 1000 >= 0) { // more than $1000 import
               importDuty += 1000 * 0.011;  // add onto rolling import duty
               importValue -= 1000;  // remove first 1000 from total import amount
               if (importValue - 12000 >= 0) {
                    importDuty += 12000 * cheeseSpecificTax;
                    importValue -= 12000; // remove next 12000 from import amount
                    if (importValue > 0) { // total import value is >= 13000
                         importDuty += importValue * 0.029;
                    }
               } else {
                    importDuty += importValue * cheeseSpecificTax;
               }
          } else { // import duty is less than 1000 
               importDuty += importValue * 0.011;
          }

          cout.setf(ios::fixed); // output dollars, so we want 2 decimal points
          cout.precision(2);

          // create final output text
          cout << "---" << endl;
          cout << "The import duty for " << importerName << " is $" << importDuty; 
     }
}