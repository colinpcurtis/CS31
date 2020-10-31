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

// check if a single state forcast is correct, which allows for easier implementation in isSyntacticallyCorrect  
bool isSyntacticallyCorrectStateForcast(string stateData) {
     string stateCode = "";
     if (stateData == "") { // empty returns true
          return true;
     }

     stateData = toUppercase(stateData);  // make entire string upper case, reduces repetition
     if (!isdigit(stateData.at(0))) { // make sure we have a digit at the start
          return false;
     }

     stateData = addDigitToFront(stateData); // add a digit onto the front, so we have length 5 string to check, reduce repetition
     if (stateData.size() <= 4) {
          return false;
     }
     stateCode = stateCode + stateData.at(2); // get single state code
     stateCode = stateCode + stateData.at(3);

     if (!isValidUppercaseStateCode(stateCode)) { // invalid state code, automatically return false
          return false;
     }
     
     for (int i = 0; i != stateData.size(); i++) { // check if there's no punctuation, spaces, or incorrectly placed digits
          char currentLoc = stateData.at(i);
          if ((i >= 2 && isdigit(currentLoc)) || (i >= 2 && !isalpha(currentLoc)) || isspace(currentLoc) || ispunct(currentLoc)) {
               return false;
          }
     }
     return true; // only return true if everything else passed  
}


// we know a valid state forcast must be of either length 4 or 5, so we can use this to create the only possible valid stateforcasts in 
// pollData string and test to see if they're valid state forcasts.  If so, we increment by either 4 or 5, 
// and if not then we return false and stop checking
bool isSyntacticallyCorrect(string pollData) {

     // quick way to make sure we have no unwanted punctuation in the string
     for (int j = 0; j!= pollData.size(); j++) { 
          if ( !isalnum(pollData.at(j)) ) {
               return false;
          }
     }

     // loop through substring state forcasts and check if they're valid
     int i = 0;
     while(i < pollData.size()) {

          // makes sure we don't get any out of range errors with missing letters at the end of the string
          if (pollData.size() - i <= 3 && pollData.size() - i >=1) {
               return false; 
          }

          // generates state forcast.  Check the shorter possibility first so we don't run into any out of range errors
          string substringStateForcast = "";
          substringStateForcast += pollData.at(i);
          substringStateForcast += pollData.at(i + 1);
          substringStateForcast += pollData.at(i + 2); 
          substringStateForcast += pollData.at(i + 3);
          
          if (isSyntacticallyCorrectStateForcast(substringStateForcast)) {
               i += 4; // jump to start of next state forecast
               continue;
          } else if (substringStateForcast.size() == pollData.size() - i) {
               return false; // if we're at the last state forcast and it's not correct, return false
          } else {
               string substringStateForcast2 = "";  // check longer state forcast
               substringStateForcast2 += pollData.at(i);
               substringStateForcast2 += pollData.at(i + 1);
               substringStateForcast2 += pollData.at(i + 2);
               substringStateForcast2 += pollData.at(i + 3);
               substringStateForcast2 += pollData.at(i + 4);

               if (isSyntacticallyCorrectStateForcast(substringStateForcast2)) { // go to next state forcast if this is correct
                    i += 5;
                    continue;
               }
               else {
                    return false;
               }
          }
     }
     return true; // only return true at end if everything else passed
}


// return true if a state forcast predicts zero electoral votes 
bool checkZeroElectoralVotes(string pollData) { 
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

          pollData = toUppercase(pollData);
          int count = 0; // num of electoral votes for party
          int index = 0; // looping variable

          // go through the entire poll string and check if the state forcast matches the party. If so, add electoral votes to count
          while (index < pollData.size()) { 

               if ( isdigit(pollData.at(index)) && isdigit(pollData.at(index + 1)) && (pollData.at(index + 4) == toupper(party)) ) {
                    string electoralVotes = "";
                    electoralVotes += pollData.at(index);
                    electoralVotes += pollData.at(index + 1); // string containing number of electoral votes
                    int votes = stoi(electoralVotes); // add onto number of 
                    count += votes;
                    index += 5; // jump to start of next state forcast
                    continue;
               } else if ( isdigit(pollData.at(index)) && (pollData.at(index + 3) == toupper(party)) ) {
                    string electoralVotes = "";
                    electoralVotes += pollData.at(index);
                    int votes = stoi(electoralVotes);
                    count += votes;
                    index += 4; // jump to start of next state forcast
                    continue;
               } else {
                    index++; // just go to next index if there's no digits and party match
               }
          }
          voteTally = count; // set voteTally to electoral count that we calculate
          cout << "vote tally: " << voteTally << endl;
          return 0;
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
