#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}


string toUppercase(string pollData) {
     string uppercase = "";
     for (int i = 0; i != pollData.size(); i++) {
          uppercase += toupper(pollData.at(i));
     }
     return uppercase;
}

// string constantLengthForcast(string pollData) {
//      string equalLengthPollData;
//      for (int i = 0; i != pollData.size(); i++) {
//           char currentPosition;
//           char lastPosition;
//           int lastIndex;
//           lastIndex = i - 1;
//           currentPosition = pollData.at(i);
//           lastPosition = pollData.at(lastIndex);
//           if (isdigit(currentPosition) && !isdigit(lastPosition)) {
//                equalLengthPollData += "0";
//           } else {
//                equalLengthPollData += currentPosition;
//           }
//      }
//      return equalLengthPollData;
// }

string addDigitToFront(string pollData) {
     if (pollData != "") {
          if (isdigit(pollData.at(0)) && !isdigit(pollData.at(1))) { // add on a digit so we have constant length of 6
               pollData = "0" + pollData;
               return pollData;
          } else {
               return pollData;
          }      
     } else {
          return "";
     }
}


bool isSyntacticallyCorrectStateForcast(string stateData) { // "55TXD" or "9OHR"
     string stateCode = "";
     if (stateData == "") {
          return true;
     }
     stateData = toUppercase(stateData);
     if (!isdigit(stateData.at(0))) { // make sure we have a digit at the start
          // cout << "stop 1" << endl;
          return false;
     }
     stateData = addDigitToFront(stateData);
     if (stateData.size() != 5) {
          // cout << "stop 2" << endl;
          return false;
     }
     stateCode = stateCode + stateData.at(2);
     stateCode = stateCode + stateData.at(3);
     if (!isValidUppercaseStateCode(stateCode)) {
          // cout << "stop 3" << endl;
          return false;
     }

     for (int i = 0; i != stateData.size(); i++) {
          char currentLoc = stateData.at(i);
          if ((i >= 2 && isdigit(currentLoc)) || (i >= 2 && !isalpha(currentLoc)) || isspace(currentLoc) || ispunct(currentLoc)) {
               // cout << "stop 4" << endl;
               return false;
          }
     }
     return true;
}

bool isSyntacticallyCorrect(string pollData) {
     int i = 0;
     while(i < pollData.size()) {
          string substringStateForcast = "";
          for (int k = i; k <= 3; k++) {
               substringStateForcast += pollData.at(k);
          }
          cout << "forcast 1 " << substringStateForcast << endl;
          if (isSyntacticallyCorrectStateForcast(substringStateForcast)) {
               i += 4;
               cout << "stop 1" << endl;
               substringStateForcast = "";
               continue;
          } else if (substringStateForcast.size() == pollData.size()) {
               return false;
          } else {
               string substringStateForcast2 = "";
               for (int l = i; l <= 4; l++) {
               substringStateForcast2 += pollData.at(l);
               }
               cout << "forcast 2 " << substringStateForcast2 << endl;
               if (isSyntacticallyCorrectStateForcast(substringStateForcast2)) {
                    i += 5;
                    cout << "stop 2" << endl;
                    substringStateForcast2 = "";
                    continue;
               }
               else {
                    return false;
               }
          }
     }
     return true;
}

// bool isSyntacticallyCorrect(string pollData) {
//      for (int i = 0; i < pollData.size(); i++) {
//           cout << i << endl;
//           string stateForcast1;
//           for (int j = i; j <=3; j++) { 
//                stateForcast1 += pollData.at(j);
//           }
//           if (isSyntacticallyCorrectStateForcast(addDigitToFront(stateForcast1))) {
//                i += 3;
//                continue;
//           } else {
//                string stateForcast2;
//                for (int j = i; j <=4; j++) { 
//                     i += 4;
//                     stateForcast2 += pollData.at(j);
//                }
//                if (isSyntacticallyCorrectStateForcast(stateForcast2)) {
//                     continue;
//                }
//                else {
//                     return false;
//                }
//                return false;
//           }
//      }
//      return true;
// }

// we know a valid state forcast must be of either length 4 or 5, so we can use this to create the only possible valid stateforcasts in pollData string and test to see if they're valid state forcasts.  If so, we increment by either 3 or 4, and if not then we return false
// bool isSyntacticallyCorrect(string pollData) {
//      int i = 0;
//      while (i < pollData.size())  {
//           string stateForcast1 = "";
//           cout << "index: " << i << endl;
//           for (int j = i; j <=3; j++) { 
//                stateForcast1 += pollData.at(j);
//           }
//           cout << "state1 " << stateForcast1 << endl;

//           // stateForcast1 = addDigitToFront(stateForcast1);
//           // check equality condition of what to do if the state forcasts are equal.  Might have consequences for empty string case.  
//           if (isSyntacticallyCorrectStateForcast(stateForcast1)) {
//                i += 4;
//                continue;
//           } else  {
//                string stateForcast2 = "";
//                for (int j = i; j <=4; j++) {
//                     stateForcast2 += pollData.at(j);
//                }
//                cout << "2: " << stateForcast2 << endl;
//                cout << "second index" << i << endl;
//                if (isSyntacticallyCorrectStateForcast(addDigitToFront(stateForcast2))) {
//                     i += 5;
//                     cout << "ran here" << endl;
//                     continue;
//                } else {
//                     return false;
//                }
//           }
//           cout << "final index: " << i << endl;
//      }
//      return true; // get to end of list, so they were all correct forcasts.  
// }


int main() {
     string forecast;
     cout << "enter a forecast: ";
     getline(cin, forecast);

     cout << "forcast is: " << isSyntacticallyCorrect(forecast) << endl;
}
