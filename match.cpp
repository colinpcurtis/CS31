#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>

using namespace std;

// match one word rule if w_in is in document
// match two word rule if w_in is in document and w_out is not in document
const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 250;


void lower(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules) { // transforms all letters to lowercase in match rules
     for (int i = 0; i < nRules; i++ ) {
          for (int j = 0; j < MAX_WORD_LENGTH; j++) {
               word1[i][j] = tolower(word1[i][j]);
               word2[i][j] = tolower(word2[i][j]);
          }
     }
}


void remove(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules, int indexToRemove) {

     char toLast1[MAX_WORD_LENGTH];
     strcpy(toLast1, word1[indexToRemove]);
     char toLast2[MAX_WORD_LENGTH];
     strcpy(toLast2, word2[indexToRemove]);

     for (int i = indexToRemove + 1; i < nRules; i++) { // have to do everything paired to ensure word order is preserved
          strcpy(word1[i-1], word1[i]);
          strcpy(word2[i-1], word2[i]);
     }
     strcpy(word1[nRules - 1], toLast1);
     strcpy(word2[nRules - 1], toLast2);
}


bool hasPunct(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int index) {
     for (int i = 0; i < MAX_WORD_LENGTH; i++) {
          if ( ispunct(word1[index][i]) || ispunct(word2[index][i]) ) {
               return false;
          }
     }
     return true;
}


void flipPos(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int srcIndex, int destIndex) {
     char temp1[MAX_WORD_LENGTH + 1];
     strcpy(temp1, word1[destIndex]);
     strcpy(word1[destIndex], word1[srcIndex]);
     strcpy(word1[srcIndex], temp1);

     char temp2[MAX_WORD_LENGTH + 1];
     strcpy(temp2, word2[destIndex]);
     strcpy(word2[destIndex], word2[srcIndex]);
     strcpy(word2[srcIndex], temp2);
}


void removePunct(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules) {
     for (int i = 0; i < nRules; i++ ) {
          for (int j = 0; j < nRules; j++) {
               if ( hasPunct(word1, word2, i) && !hasPunct(word1, word2, j) ) { 
                    // flip positions in string until all non-punct elements are at front
                    flipPos(word1, word2, i, j);
               }
          }
     }
}


void removeDuplicates(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules) {
     for (int i = 0; i < nRules; i++) {
          if ( strcmp(word1[i], word2[i]) == 0) {
               remove(word1, word2, nRules, i);
          }
     }

     for (int i = 0; i < nRules; i++) { // remove any w_in one word rules that have duplicates
          for (int j = 0; j < nRules; j++) {
               if ( strcmp(word1[i], word2[j]) == 0 && strcmp(word2[i], "") == 0) {
                    remove(word1, word2, nRules, j); // remove j so that we maintain the current position
               }
          }
     }
}


void checkEmptyString(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], 
                      int  nRules) {
     // need word2 as a parameter since we'll need to flip word pairs if there's an empty string and preserve the order
     for (int i = 0; i < nRules; i++) {
          if ( strcmp(word1[i], "") == 0 ) { 
               remove(word1, word2, nRules, i); // compare with empty string and place it at the end
          }
     }
}


bool checkIfPresent(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], 
     char checkWord[MAX_WORD_LENGTH + 1], int nRules, int pos) {

     for (int i = pos - 1; i >= 0 ; i--) {
          if ( strcmp(word2[i], "") == 0 && strcmp(word1[i], checkWord) == 0) {
               return true;
          }
     }
     return false;
}


int cleanupRules(char wordin[][MAX_WORD_LENGTH + 1], char wordout[][MAX_WORD_LENGTH + 1], int nRules) {
     
     // cleans the array according to the rules
     lower(wordin, wordout, nRules);
     removePunct(wordin, wordout, nRules);
     removeDuplicates(wordin, wordout, nRules);
     checkEmptyString(wordin, wordout, nRules);

     for (int i = 0; i < nRules; i++) {
          cerr << wordin[i] << " " << wordout[i] << endl;
     }
     
     for (int i = 0; i < nRules; i++) {
          
           // check all failing conditions
          if ( strcmp(wordin[i], "") == 0 || strcmp(wordin[i], wordout[i]) == 0  || checkIfPresent(wordin, wordout, wordin[i], nRules, i) || 
          !hasPunct(wordin, wordout, i) ) {
               // cerr << endl;
               // cerr << wordin[i] << " " << wordout[i] << endl;
               // cerr << "ran here" << endl;
               return i; // return num of matches, but with zero-indexing we return the correct number.  
          }
     }
     return 0;
}


bool wordInDoc(const char document[], const char word1[]) {

     // check if sequence of positions matches word1
     for (int i = 0; i < strlen(document) - strlen(word1) + 1; i++) {
          int numMatches = 0;
          for (int j = 0; j < strlen(word1); j++) {
               if ( document[i + j] == word1[j] ) { // corresponding position in document
                    numMatches++;
               }
          }
          if (numMatches == strlen(word1)) { // sequence word1 occurs in document
               return true;
          }
     }
     return false;
}


// bool substring(const char document[], const char word1[], const char word2[]) {
//      int matches = 0;

//      for (int i = 0; i < MAX_DOCUMENT_LENGTH - strlen(word1) + 1; i++) {
//           int numMatches1 = 0;
//           int numMatches2 = 0;
//           for (int j = 0; j < strlen(word1); j++) {
//                if ( document[i + j] == word1[j] ) {
//                     numMatches1++;
//                     // cerr << document[i + j] << " " << word1[j] << endl;
//                }
//           }


//           // for (int j = 0; j <= i - strlen(word2) - 1; j++) {
//           //      if ( document[i + j] == word2[j] ) {
//           //           numMatches2++;
//           //      }
//           // }
//           if (numMatches1 == strlen(word1)) {
//                return true;
//           }
//      }

//      for (int i = 0; i < MAX_DOCUMENT_LENGTH - strlen(word2) + 1; i++) {
//           int numMatches1 = 0;
//           int numMatches2 = 0;
//           for (int j = 0; j < strlen(word2); j++) {
//                if ( document[i + j] == word2[j] ) {
//                     numMatches1++;
//                     cerr << document[i + j] << " " << word2[j] << endl;
//                }
//           }


//           // for (int j = 0; j <= i - strlen(word2) - 1; j++) {
//           //      if ( document[i + j] == word2[j] ) {
//           //           numMatches2++;
//           //      }
//           // }
//           if (numMatches1 == strlen(word2)) {
//                matches++;
//           }
//      }

//      return false;
// }


int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH+1], const char wordout[][MAX_WORD_LENGTH+1], int nRules) {
     
     char cleanStr[MAX_DOCUMENT_LENGTH + 1];
     strcpy(cleanStr, document);

     // set chars to lowercase and only keep alphabetic or space characters
     int badStringPositions = 0; // keeps track non-alpha or non-space chars 
     int lenOfString = 0; // keeps track of times we shift over to reset zero byte at end
     for (int i = 0; i < strlen(document); i++) {
         
          // cout << newDoc[i] << endl;
          if ( isalpha(document[i]) || isspace(document[i]) ) {
               cleanStr[i - badStringPositions] = tolower(document[i]);
               // cerr << i << " " << removedStr[i] << endl;
               lenOfString++; // increment length of string 
          } else {
               badStringPositions++;
          }
     }
     cleanStr[lenOfString] = '\0'; // reset zero byte
     // cerr << endl;
     // cerr << cleanStr << endl;
     // cerr << endl;


     // determine score
     int score = 0;
     for (int i = 0; i < nRules; i++) {
          if (strcmp(wordout[i], "") == 0){ // one word rule 
               score++;
          }
          else if ( wordInDoc(document, wordin[i]) && !wordInDoc(document, wordout[i])) { // two word rule
               score++;
          }
     }
     return score;
}


int main() {
     const int TEST1_NRULES = 12;
     char test1win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
          "confusion", "family", "charm", "hearty", "house", "worn-out", "family", "charm", "ties", "", "charm", "FaMily" };

     char test2win[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
          "", "ties", "confusion", "hearty", "intrigue", "younger", "first", "", "family", "frightened", "", "ties" };

     // lower("Happy families are all alike; every unhappy family is unhappy in its own way.");
     // lower("I'm upset that on Nov. 13th, 2020, my 2 brand-new BMW M850is were stolen!!");
     // bool x = substring("im upset that on nov th my bmw was stolen", "was", "was");

     // bool x = wordInDoc("im upset that on nov th my bmw was stolen", "was");
     // assert(wordInDoc("im upset that on nov th my bmw was stolen", "was") == 1);
     // assert(wordInDoc("im upset that on nov th my bmw was stolen", "try") == 0);
     // assert(wordInDoc("im upset that on nov th my bmw was stolen", "the") == 0);
     // assert(wordInDoc("im upset that on nov th my bmw was stolen", "stolen") == 1);


     const char document[MAX_DOCUMENT_LENGTH + 1] = "im upset that on family th my ties was stolen and i have confusion";
     int x = determineScore(document, test1win, test2win, 1);
     cerr << "result: " << x << endl;


     // cerr << x << endl;
     // int x = cleanupRules(test1win, test2win, 0);
     // cout << "returned: " << x << endl;
}