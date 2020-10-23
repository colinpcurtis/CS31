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


bool isValidNumber(string number) {
    const string codes =
        "1.2.3.4.5.6.7.8.9.0.";
    return ((number.size() == 2 || number.size() == 1)  &&
            number.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(number) != string::npos);  // match found
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
          }
          
     } else {
          return "";
     }
     return pollData;
}


bool isSyntacticallyCorrectStateForcast(string pollData) { // "55TXD" or "9OHR"
     string stateCode = "";
     if (pollData == "") {
          return true;
     }
     pollData = toUppercase(pollData);
     if (!isdigit(pollData.at(0))) { // make sure we have a digit at the start
          cout << "stop 1" << endl;
          return false;
     }
     if (isdigit(pollData.at(0)) && !isdigit(pollData.at(1))) { // add on a digit so we have constant length of 6
          pollData = "0" + pollData;
     }
     if (pollData.size() != 5) {
          cout << "stop 2" << endl;
          return false;
     }
     stateCode = stateCode + pollData.at(2);
     stateCode = stateCode + pollData.at(3);
     if (!isValidUppercaseStateCode(stateCode)) {
          cout << "stop 3" << endl;
          return false;
     }

     for (int i = 0; i != pollData.size(); i++) {
          char currentLoc = pollData.at(i);
          if ((i >= 2 && isdigit(currentLoc)) || (i >= 2 && !isalpha(currentLoc)) || isspace(currentLoc)) {
               cout << "stop 4" << endl;
               cout << i << endl;
               return false;
          }
     }
     return true;
}

// we know a valid state forcast must be of either length 4 or 5, so we can use this to create the only possible valid stateforcasts in pollData string and test to see if they're valid state forcasts.  If so, we increment by either 3 or 4, and if not then we return false
bool isSyntacticallyCorrect(string pollData) {
     int i = 0;
     while (i <= pollData.size()) {
          string stateForcast1 = "";
          string stateForcast2 = "";
          for (int i = 0; i <=3; i++) { 
               stateForcast1 += pollData.at(i);
          }
          for (int i = 0; i <=4; i++) {
               stateForcast1 += pollData.at(i);
          }

          stateForcast1 = addDigitToFront(stateForcast1);
          // check equality condition of what to do if the state forcasts are equal.  Might have consequences for empty string case.  
          if (isSyntacticallyCorrectStateForcast(stateForcast1)) {
               i += 4;
               continue;
          } else if (isSyntacticallyCorrectStateForcast(stateForcast2)) {
               i += 5;
               continue;
          } else {
               return false;
          }
     }
     cout << "end";
     return true; // get to end of list, so they were all correct forcasts.  
}


int main() {
     string forecast;
     cout << "enter a forecast: ";
     getline(cin, forecast);

     cout << "forcast is: " << isSyntacticallyCorrect(forecast) << endl;
}
