#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>

using namespace std;

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


bool hasPunct(char word1[][MAX_WORD_LENGTH + 1], int index) {
     // loop through string positions and check if they have punctuation
     for (int i = 0; i < strlen(word1[index]); i++) {
          if ( !isalpha(word1[index][i]) ) {
               return true;
          }
     }
     return false;
}

// bool validOneWordRule( char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], char checkWord[MAX_WORD_LENGTH + 1], int nRules ) {
//      // if (strcmp(checkWord, "") == 0 ) { // empty one word rule is invalid
//      //      return true;
//      // }
//      for (int i = 0; i < nRules; i++) {
//           // cerr << i << " " <<word1[i] << " " << checkWord << " " << word2[i] << endl;
          
//           if ( strcmp(word1[i], checkWord) == 0 && strcmp(word2[i], "") == 0 ) {
//                cerr << word1[i] << " " << checkWord << endl;
//                return true;
//           }
//      }
//      return false;
// }


// bool invalidTwoWordRule( char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], char checkWord1[MAX_WORD_LENGTH + 1], 
//                        char checkWord2[MAX_WORD_LENGTH + 1], int nRules, int pos) {

//      if (strcmp(checkWord1, "") == 0 || (strcmp(checkWord1, checkWord2) == 0) ) {
//           return true;
//      }
//      // int numOccurences = 0;
//      for (int i = 0; i < nRules ; i++) {
//           // if ( /*strcmp(word2[i], "") != 0 && */ i != pos && strcmp(word1[i], checkWord1) == 0 && strcmp(word2[i], checkWord2) == 0  /*|| 
//           //      (strcmp(word1[i], checkWord1) == 0 && strcmp(checkWord2, "") == 0)*/ ) {

//           //      cerr << word1[i] << " " << checkWord1 << " "<< word2[i] << " " << checkWord2 << endl;
//           //      return true;
//           // }
//           // cerr << i << " " <<word1[i] << " " << checkWord1 << " "<< word2[i] << " " << checkWord2 << endl;
//           if ( /*i != pos &&  ( strcmp(word1[i], checkWord1) == 0 && strcmp(word2[i], checkWord2) == 0 )
//                || */ (strcmp(word1[i], checkWord1) == 0 &&  strcmp(word2[i], "") == 0) /*|| (strcmp(word1[i], "") == 0) */) {
//                // not checking same element, both in and out words are equal, wordin matches one word rule
               
//                return true;
//           }
//      }
//      return false;
// }


bool isPreviouslyPresent( char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], 
                          char checkword1[MAX_WORD_LENGTH + 1], char checkword2[MAX_WORD_LENGTH + 1], int pos) {
     
     for (int i = 0; i < pos; i++) {
          if ( (strcmp(word1[i], checkword1) == 0 && strcmp(word2[i], checkword2) == 0) || 
               (strcmp(word1[i], checkword1) == 0 && strcmp(word2[i], "") == 0) ) {
                    // cerr << word1[i] << " " << word2[i] << checkword1 << " " << checkword2 << endl; 
               return true;
          }
     }
     return false;
}

void toFront(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules, int src, int dest) {
     // used to put one word rules at the front of the word arrays
     char tofront1[MAX_WORD_LENGTH];
     strcpy(tofront1, word1[src]); // use temp variables to flip positions
     char tofront2[MAX_WORD_LENGTH];
     strcpy(tofront2, word2[src]);

     for (int i = src; i < nRules; i++) { // have to do everything paired to ensure word order is preserved
          strcpy(word1[i], word1[i + 1]);
          strcpy(word2[i], word2[i + 1]);
     }
     strcpy(word1[dest], tofront1);
     strcpy(word2[dest], tofront2);
}

bool notInPrevious( char wordin[][MAX_WORD_LENGTH + 1], char wordout[][MAX_WORD_LENGTH + 1],
                    char checkword1[MAX_WORD_LENGTH + 1], char checkword2[MAX_WORD_LENGTH + 1], int pos) {
     // make sure that when we want to add a new word rule that we don't have any word in matches or otherwise failing conditions
     for (int i = 0; i < pos; i++) {
          if ( strcmp(checkword1, wordin[i]) == 0 && strcmp(checkword2, wordout[i]) == 0 ) { // check words match a word rule
               return false;
          } 
     }
     return true;
}

int cleanupRules(char wordin[][MAX_WORD_LENGTH + 1], char wordout[][MAX_WORD_LENGTH + 1], int nRules) {
     lower(wordin, wordout, nRules);

     int badPositions = 0;
     int goodPositions = 0;
     int numOneWordRules = 0;

     // put one word rules at the front of the array for easy checking of two word rules
     for (int i = 0; i < nRules; i++) {
          if (strcmp(wordin[i], "") != 0 && strcmp(wordout[i], "") == 0 && !hasPunct(wordin, i) ) {
               toFront(wordin, wordout, nRules, i, numOneWordRules); // put valid word rule at front 
               numOneWordRules++;
          }
     }

     for (int i = 0; i < nRules; i++) {
          cerr << wordin[i] << " " << wordout[i] << endl;
     }
     cerr << endl;


     for (int i = 0; i < nRules; i++) { // loop through all word rules
          
          if ( strcmp(wordin[i], wordout[i]) != 0 && strcmp(wordin[i], "") != 0 
               && notInPrevious(wordin, wordout, wordin[i], wordout[i], goodPositions) && !hasPunct(wordin, i) && !hasPunct(wordout, i) 
                ) {
          // if word rule doesn't match previous word rules or other failing conditions, place it at the next position in the word arrays
               strcpy(wordin[i - badPositions], wordin[i]);
               strcpy(wordout[i - badPositions], wordout[i]);
               goodPositions++; // increment matching word rules
          } else {
               badPositions++; // position didn't match, so it needs to be replaced
          }
     }

     for (int i = 0; i < goodPositions; i++) {
          cerr << wordin[i] << " " << wordout[i] << endl;
     }
     cerr << goodPositions << endl;
     return goodPositions;
}


bool nextCharSpace(const char document[], int pos) {
     // make sure that when we identify a word, it is followed by a space or ends the document
     if (pos > strlen(document)) {
          return false;
     }
     else if (pos == strlen(document) || isspace(document[pos]) ) { // check strlen first because of out of bounds
          // if it ends the eocument then we want to return true
          return true;
     }
     return false;
}


bool wordInDoc(const char document[], const char word1[]) { // check if word is in document

     int loopBound; 
     // in some cases the length of the words can be longer than the document
     // so need to ensure that we get no out of bounds errors

     if ( strlen(document) >= strlen(word1) ) {
          loopBound = strlen(document) - strlen(word1) + 1; // ensures no out of range errors
     } else {
          loopBound = strlen(word1);
     }

     // check if sequence of positions matches word1
     for (int i = 0; i < loopBound; i++) {
          int numMatches = 0;
          for (int j = 0; j < strlen(word1); j++) {
               if ( document[i + j] == word1[j] ) { // corresponding position in document
                    numMatches++;
               }
          }
          if (numMatches == strlen(word1)  && nextCharSpace(document, i + strlen(word1)) ) {
               // sequence word1 occurs in document and is followed by space
               return true;
          }
     }
     return false;
}


int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH+1], const char wordout[][MAX_WORD_LENGTH+1], int nRules) {
     
     char cleanStr[MAX_DOCUMENT_LENGTH + 1];
     strcpy(cleanStr, document);


     // set chars to lowercase and only keep alphabetic or space characters
     int badStringPositions = 0; // keeps track non-alpha or non-space chars 
     int lenOfString = 0; // keeps track of times we shift over to reset zero byte at end
     for (int i = 0; i < strlen(document); i++) {

          if ( isalpha(document[i]) || isspace(document[i]) ) {
               cleanStr[i - badStringPositions] = tolower(document[i]); // position is shifted to account for punctuation characters
               lenOfString++; // increment length of string 
          } else {
               badStringPositions++;
          }
     }
     cleanStr[lenOfString] = '\0'; // reset zero byte to len of string


     // determine score
     int score = 0;
     for (int i = 0; i < nRules; i++) {
          // cerr << wordin[i] << " " << wordout[i] <<  " " << cleanStr[i] << endl;
          if (strcmp(wordout[i], "") == 0 && wordInDoc(cleanStr, wordin[i]) ){ // one word rule 
               score++;
          }
          else if ( wordInDoc(cleanStr, wordin[i]) && !wordInDoc(cleanStr, wordout[i])) { // two word rule
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

     char word1in[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
          "confusion", "confusion", "", "charm", "house", "worn-out", "family", "charm", "ties", "", "charm", "FaMily" };

     char word2in[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
          "hi", "hi", "confusion", "hearty", "intrigue", "younger", "first", "", "family", "frightened", "", "ties" };
     
     // int x = cleanupRules(word1in , word2in, 5);
     // cerr << x << endl;

     // replaceString(word1in, word2in, 5);
     // int x = cleanupRules(word1in, word2in, 5);
     // cerr << x << endl;

     // toFront(test1win, test2win, 12, 7, 1);

     // assert( checkIfWordPresent( word1in, word2in, ))

     // oneWordRulesLast(test1win, test2win, 12);

     assert( cleanupRules(test1win, test2win, 12) == 6 );

     // assert( isPreviouslyPresent(test1win, test2win, "charm", "confusion", 2) == 0);

     // assert( invalidOneWordRule(test1win, test2win, "confusion", 12, 0) == 1 );
     // assert( invalidOneWordRule(test1win, test2win, "hi", 12, 6) == 0 );
     // assert( invalidOneWordRule(test1win, test2win, "charm", 12, 10) == 1  );

     // assert( invalidTwoWordRule(test1win, test2win, "family", "ties", 12, 3) == 0 );
     // assert( invalidTwoWordRule(test1win, test2win, "family", "ties", 12, 11) == 1 );
     // assert ( invalidTwoWordRule(test1win, test2win, "charm", "", 12, 10) == 1);
     // assert( invalidTwoWordRule(test1win, test2win, "family", "first", 12, 6) == 0 );

     cerr << "all passed" << endl;
     

     // char checkword[MAX_WORD_LENGTH + 1] = "confusion";
     // bool x = checkIfPresent(word1in, word2in, checkword, 0);
     // cerr << x << endl;
     // assert(wordInDoc("im upset that on nov th my bmw was stolen", "was") == 1);
     // assert(wordInDoc("im upset that on nov th my bmw was stolen", "try") == 0);
     // assert(wordInDoc("im upset that on nov th my bmw was stolen", "the") == 0);
     // assert(wordInDoc("im upset that on nov th my bmw was stolen", "stolen") == 1);

     
     // const int TEST1_NRULES = 3;
     // const char document[MAX_DOCUMENT_LENGTH + 1] = "im upset that on family th my ties was stolen and have i";
     // char wordin[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"i",};
     // char wordout[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"",};

     //      char test1win[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "family", "unhappy", "horse", };
     //      char test1wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"",       "horse",   "", };
     //      assert(determineScore("Happy families are all alike; every unhappy family is unhappy in its own way.",
     //                    test1win, test1wout, TEST1_NRULES) == 2);
     //      assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
     //                    test1win, test1wout, TEST1_NRULES-1) == 0);
     //      assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
     //                    test1win, test1wout, TEST1_NRULES) == 1);
     //      assert(determineScore("A horse!  A horse!  My kingdom for a horse!",
     //                    test1win, test1wout, TEST1_NRULES) == 1);
     //      assert(determineScore("horse:stable ratio is 10:1",
     //                    test1win, test1wout, 0) == 0);
     //      assert(determineScore("**** 2020 ****",
     //                    test1win, test1wout, -1) == 0);

     //      assert(determineScore(document, wordin, wordout, 1) == 1);
     //      cout << "All tests succeeded" << endl;

}