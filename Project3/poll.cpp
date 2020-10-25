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

// string constantLength(string forcastString) {
//      for (int i = 0; i < forcastString.size(); i++){
//           if (isdigit(forcastString.at(i) && isdigit(forcastString.at(i + 1))) {
//                continue;
//           } else if(isdigit(forcastString.at(i) &&)){
               
//           }
//      }

// }


string toUppercase(string pollData) {
     string uppercase = "";
     for (int i = 0; i != pollData.size(); i++) {
          uppercase += toupper(pollData.at(i));
     }
     return uppercase;
}

// adding digit to front if the state forcast is length 4; ie 5riD, then changing it to 05riD makes it easier to check in other functions
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


// we know a valid state forcast must be of either length 4 or 5, so we can use this to create the only possible valid stateforcasts in pollData string and test to see if they're valid state forcasts.  If so, we increment by either 3 or 4, and if not then we return false and stop checking the string 
bool isSyntacticallyCorrect(string pollData) {
     int i = 0;
     while(i < pollData.size()) {
          
          // cout << "index " << i << endl; 
          string substringStateForcast = "";
          substringStateForcast += pollData.at(i);
          substringStateForcast += pollData.at(i + 1);
          substringStateForcast += pollData.at(i + 2);
          substringStateForcast += pollData.at(i + 3);
          
          // cout << "forcast 1 " << substringStateForcast << endl;
          if (isSyntacticallyCorrectStateForcast(substringStateForcast)) {
               i += 4;
               // cout << "stop 1" << endl;
               continue;
          } else if (substringStateForcast.size() == pollData.size() - i) {
               return false;
          } else {
               string substringStateForcast2 = "";
               substringStateForcast2 += pollData.at(i);
               substringStateForcast2 += pollData.at(i + 1);
               substringStateForcast2 += pollData.at(i + 2);
               substringStateForcast2 += pollData.at(i + 3);
               substringStateForcast2 += pollData.at(i + 4);
               // cout << "forcast 2 " << substringStateForcast2 << endl;
               if (isSyntacticallyCorrectStateForcast(substringStateForcast2)) {
                    i += 5;
                    // cout << "stop 2" << endl;
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
// TODO: check 00 case
bool checkZeroElectoralVotes(string pollData) { // return true if a state forcast predicts zero electoral votes
     for (int i = 0; i < pollData.size(); i++) {
          if (pollData.at(i) == '0' && !isdigit(pollData.at(i + 1))) {
               return true;
          } else if (pollData.at(i) == '0' && pollData.at(i + 1) == '0') {
               return true;
          }
     }
     return false;
}


int tallyVotes(string pollData, char party, int& voteTally) {

     if (!isSyntacticallyCorrect(pollData)){
          return 1;
     } else if (!isalpha(party)) {
          return 2;
     } else if (checkZeroElectoralVotes(pollData)) {
          return 3;
     } else {
          int count = 0;
          int index = 0; // looping variable
          while (index < pollData.size()) {
               string electoralVotes = pollData.substr(index, 2);
               cout << "electoral votes " << electoralVotes << endl;
               if (isdigit(pollData.at(index) && isdigit(pollData.at(index + 1)))) {
                    string electoralVotes = pollData.substr(index, 2);
                    cout << "electoral votes " << electoralVotes << endl;
               }
               // } else if (isdigit(pollData.at(index) && !isdigit(pollData.at(index + 1)))) {
               //      electoralVotes += pollData.at(index);
               // }
               // cout << "votes " << electoralVotes << endl;

               // string stateForcast = "";

               // stateForcast += pollData.at(index);
               // stateForcast += pollData.at(index + 1);
               // if (isValidUppercaseStateCode(stateForcast) && (pollData.at(index + 2) == party || pollData.at(index + 2) == toupper(party))) {
               //      if (isdigit(pollData.at(index - 1)))
               // }
               break;
          }
          return 4;
     }


     
}

int main() {
     string forecast;
     char party;
     int voteTally;
     cout << "enter a forecast: ";
     getline(cin, forecast);
     cout << "enter a party ";
     cin >> party;
     cin.ignore(1000, '\n');

     cout << "vote tally ";
     cin >> voteTally;

     cout << "forcast is: " << tallyVotes(forecast, party, voteTally) << endl;
}
