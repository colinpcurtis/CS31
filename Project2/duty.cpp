#include <iostream>
#include <string>
using namespace std;

int main() {
     double cheeseSpecificTax;
     // initialize and declare variables
     string cheeseName;
     double importValue;
     string importerName;
     double importDuty = 0.0;

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
          if (importValue - 1000 >= 0) {
               importDuty += 1000 * 0.011;
               importValue -= 1000;
               cout << "step 1" << endl;
               if (importValue - 12000 >= 0) {
                    importDuty += 12000 * cheeseSpecificTax;
                    importValue -= 12000;
                    cout << "step 2" << endl;
                    if (importValue > 0) {
                         importDuty += importValue * .029;
                         cout << "step 3" << endl;
                    }
               } else {
                    importDuty += importValue * cheeseSpecificTax;
                    cout << "step 4" << endl;
               }
          } else {
               importDuty += importValue * 0.011;
               cout << "step 5" << endl;
          }

          cout.setf(ios::fixed); // output dollars, so we want 2 decimal points
          cout.precision(2);

          // create final output text

          cout << "---" << endl;
          // if (cheeseName == "") {
          //      cout << "You must enter a cheese type";
          // } else if (importValue <= 0) { // make sure if we want equal case
          //      cout << "The value must be positive";
          // } else if (importerName == "") {
          //      cout << "You must enter an importer";
          // } else {
               cout << "The import duty for " << importerName << " is $" << importDuty; 
     }
}