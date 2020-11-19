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
          if ( ispunct(word1[index][i]) ) {
               return true;
          }
     }
     return false;
}

bool invalidOneWordRule( char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], char checkWord[MAX_WORD_LENGTH + 1], int nRules, 
                         int pos) {
     if (strcmp(checkWord, "") == 0 ) { // empty one word rule is invalid
          return true;
     }
     for (int i = 0; i < nRules; i++) {
          // cerr << i << " " <<word1[i] << " " << checkWord << " " << word2[i] << endl;
          
          if ( /*strcmp(word2[i], "") == 0 &&*/ i != pos && (strcmp(word1[i], checkWord) == 0 || strcmp(word2[i], "") != 0
          /*|| strcmp(checkWord, "") == 0*/  )) {
               // cerr << word1[i] << " " << checkWord << endl;
               return true;
          }
     }
     return false;
}


bool invalidTwoWordRule( char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], char checkWord1[MAX_WORD_LENGTH + 1], 
                       char checkWord2[MAX_WORD_LENGTH + 1], int nRules, int pos) {

     if (strcmp(checkWord1, "") == 0 || (strcmp(checkWord1, checkWord2) == 0) ) {
          return true;
     }
     int numOccurences = 0;
     for (int i = 0; i < nRules ; i++) {
          // if ( /*strcmp(word2[i], "") != 0 && */ i != pos && strcmp(word1[i], checkWord1) == 0 && strcmp(word2[i], checkWord2) == 0  /*|| 
          //      (strcmp(word1[i], checkWord1) == 0 && strcmp(checkWord2, "") == 0)*/ ) {

          //      cerr << word1[i] << " " << checkWord1 << " "<< word2[i] << " " << checkWord2 << endl;
          //      return true;
          // }
          // cerr << i << " " <<word1[i] << " " << checkWord1 << " "<< word2[i] << " " << checkWord2 << endl;
          if ( i != pos && ( strcmp(word1[i], checkWord1) == 0 && strcmp(word2[i], checkWord2) == 0 )
               || (strcmp(word1[i], checkWord1) == 0 &&  strcmp(word2[i], "") == 0) /*|| (strcmp(word1[i], "") == 0) */) {
               // not checking same element, both in and out words are equal, wordin matches one word rule
               
               return true;
          }
     }
     return false;
}


bool checkIfWordPresent(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules, int pos) {
     // see if word in has duplicates prior to current position
     for (int i = 0; i < nRules ; i++) { // start at pos - 1 so we don't identify current position
          // if ( (strcmp(word2[i], "") == 0 && strcmp(word1[i], checkWord) == 0) ||  
          //      (strcmp(word2[i], "") != 0 && strcmp(word1[i], checkWord) == 0 ) ) { 
          //           // check if the word rule occurs multiple times || strcmp(word2[i], checkWord) == 0 ))
          //      return true;
          // }

          // if ( !invalidOneWordRule(word1, word2, word1[i], i) || !invalidTwoWordRule(word1, word2, word1[i], word2[i], i) ) {
          //      return true;
          // }
          if ( strcmp(word2[i], "") == 0 ) {
               if ( invalidOneWordRule(word1, word2, word1[i], nRules, i) ) {
                    return true;
               }
          } else {
               if ( invalidTwoWordRule(word1, word2, word1[i], word2[i], nRules, i) ) {
                    return true;
               }
          }
     }
     return false;
}


// void checkValidPositions(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules) {
//      // dont need char checkWord[MAX_WORD_LENGTH + 1] parameter
//      for (int i = 0; i < nRules; i++) {
//           if ( checkIfPresent(word1, word2, word1[i], nRules) ) {
//                     remove(word1, word2, nRules, i); 
//           }
//           // for (int j = 0; j < nRules; j++) {
               
//           // }
//      }
// }


// void replaceString(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nRules) {
//      char newStringin[nRules][MAX_WORD_LENGTH + 1];
//      char newStringout[nRules][MAX_WORD_LENGTH + 1];
     
//      int counter = 0;
//      int badPositions = 0;
//      for (int i = 0; i < nRules; i++) { // loop through word rules, if they acceptable word rules, add them to front, else add to back
          
//           if ( strcmp(word1[i], "") != 0 && strcmp(word1[i], word2[i]) != 0  && !checkIfWordPresent(word1, word2, word1[i], i) 
//                && !hasPunct(word1, i) && !hasPunct(word2, i) ) {

//                counter++;
//                strcpy(newStringin[i- badPositions], word1[i]);
//                strcpy(newStringout[i - badPositions], word2[i]);
               
//           }
//           else {
//                badPositions++;
//           }
//      }
//      cerr << endl;
//      cerr << "result" << endl;
//      for (int i = 0; i < nRules; i++) {
//           cerr << newStringin[i] << " " << newStringout[i] << endl;
//      }
//      cerr << counter << endl;
// }


int cleanupRules(char wordin[][MAX_WORD_LENGTH + 1], char wordout[][MAX_WORD_LENGTH + 1], int nRules) {
     
     // cleans the array according to the rules
     lower(wordin, wordout, nRules);
     // removePunct(wordin, wordout, nRules);
     char newStringin[nRules][MAX_WORD_LENGTH + 1];
     char newStringout[nRules][MAX_WORD_LENGTH + 1];
     
     int validWordRules = 0; // number of valid word rules
     int badPositions = 0; // keep track of invalid positions in string
     // for (int i = 0; i < nRules; i++) { 
     //      // cerr << wordin[i] << " " << wordout[i] << endl;
     //      // loop through word rules, if they acceptable word rules, add them to front and increment counter
          
     //      if ( strcmp(wordin[i], "") != 0 && strcmp(wordin[i], wordout[i]) != 0   && !checkIfWordPresent(wordin, wordout, i) &&
     //      /*&& !invalidOneWordRule(wordin, wordout, wordin[i], i) &&   
     //           !invalidTwoWordRule(wordin, wordout, wordin[i], wordout[i], i) && */ !hasPunct(wordin, i) && !hasPunct(wordout, i) ) {
               
     //           strcpy(newStringin[i- badPositions], wordin[i]);
     //           strcpy(newStringout[i - badPositions], wordout[i]);
     //           validWordRules++;
     //      }
     //      else {
     //           badPositions++;
     //      }
     // }

     for (int i = 0; i < nRules; i++) {
          if ( !invalidTwoWordRule(wordin, wordout, wordin[i], wordout[i], nRules, i) 
               && !hasPunct(wordin, i) && !hasPunct(wordout, i) ) {

               strcpy(newStringin[i- badPositions], wordin[i]);
               strcpy(newStringout[i - badPositions], wordout[i]);
               validWordRules++;
          } else if ( !invalidOneWordRule(wordin, wordout, wordin[i], nRules, i) && !hasPunct(wordin, i) && !hasPunct(wordout, i) ) {
               cerr << wordin[i] << " " << wordout[i] << endl;

               strcpy(newStringin[i- badPositions], wordin[i]);
               strcpy(newStringout[i - badPositions], wordout[i]);
               validWordRules++;
          } else {
               badPositions++;
          }
     }

     // for (int i = 0; i < nRules; i++) {
     //      cerr << i << " " <<wordin[i] << " " << wordout[i] << endl;
     //      if ( /*checkIfWordPresent(wordin, wordout, nRules, i)*/ 
     //           (invalidOneWordRule(wordin, wordout, wordin[i], nRules, i) && invalidTwoWordRule(wordin, wordout, wordin[i], wordout[i], nRules, i) )  && !hasPunct(wordin, i) && !hasPunct(wordout, i)) {

     //           strcpy(newStringin[i- badPositions], wordin[i]);
     //           strcpy(newStringout[i - badPositions], wordout[i]);
     //           validWordRules++;
     //      } else {
     //           badPositions++;
     //      }
     // }
     cerr << endl;
     cerr << "result " << validWordRules << endl;
     cerr << "bad positions " << badPositions << endl;
     for (int i = 0; i < validWordRules; i++) {
          cerr << newStringin[i] << " " << newStringout[i] << endl;
     }

     return validWordRules;
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
     cleanStr[lenOfString] = '\0'; // reset zero byte


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

     // assert( checkIfWordPresent( word1in, word2in, ))

     assert( cleanupRules(test1win, test2win, 12) == 6 );

     // assert( invalidOneWordRule(test1win, test2win, "confusion", 12, 0) == 0 );
     // assert( invalidOneWordRule(test1win, test2win, "hi", 12, 6) == 0 );
     // assert( invalidOneWordRule(test1win, test2win, "charm", 12, 10) == 1  );

     // assert( invalidTwoWordRule(test1win, test2win, "hearty", "hearty", 12, 3) == 1 );
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