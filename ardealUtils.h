#ifndef __cplusplus
typedef unsigned char bool;
static const bool false = 0;
static const bool true = 1;
#endif

#ifndef ARDEALUTILS
#define ARDEALUTILS

#define NO "no"
#define NI "ni"
#define MA "ma"
#define TU "tu"
#define LA "la"
#define EL "el"
#define CE "ce"
#define BE "be"

/// Takes as input 2 chars from the ardeal language and executes code based on the combination 
/// Returns 1 for all words, except if the word is a loop word ('NO'), then it returns 0
/// returns -1 if unrecognized command
int executeWord(char *ardealWord);

///executes the codeArray, isLoop indicates if this is a sub-array representing a loop
void executeArdealCode(char *ardealCodeArray);

///searches starting from the end of the code array for the loop terminator EL until currentPos(loop beginning)
///returns the position of the last char of the word (char pos of 'L' from 'EL')
///returns -1 if it can't find the loop terminator, this is a logic error
int findLastLoopTerminator(char *ardealCodeArray, int currentPos);

///check if the word is 2-chars in length and then check if it is one of the 8 vocabulary words
bool checkWord(char *currentWord);

void memDump(int low, int high);
	
#endif
