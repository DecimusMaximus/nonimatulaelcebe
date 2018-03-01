/*
25/02/2018
MaximusDecimus@github

A little brainfuck clone with commands replaced by "ardeal language" words
Current bug: must always end the .no code file with an endline character ('\n')

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ardealUtils.h"

int DEBUG = 0; // default to 0, set throguh program argument to 1 to show debug messages
//2 to show individual commands
//3 to pause on each command and show pointer value for {interval} cells of memory


char programArray[32768] = { 0 }; //32kB memory all set to 0
char *ptr = programArray;
char lineBuffer[300]; //maximum of 300 chars per line allowed
char *codeArray = NULL; //to be allocated based on size of the file
int codeIndex = 0;
char wordBuffer[10]; //10 to account for possible grave syntax erorrs, but words are max 2 chars

/* Program steps:
1. Read line by line the input file into a line buffer
2. Check the line buffer for any errors in syntax (words longer than 2 chars and missing spaces)
This way we can easily point the error location.
3. If syntax is correct, put the line buffer in the code memory
4. Run the code, word by word. If loop begin detected, check if it also ends otherwise end program in error

*/
int main(int argc, char **argv) {
	if (argv[1] == NULL) {
		printf("\n Ai die capu meu! \n");
		printf("[EN] You must provide the name of .no file as an argument \n");
		printf("[RO] Trebuie sa dati ca parametru numele fisierului .no \n");
		printf("[ARDEAL] No ma, dapu n-ai dat ca parametru numele fisierului no, ase-i? \n");
		return -1;
	}

	if (argv[2] != NULL) {
		if (*argv[2] == '1') {
			DEBUG = 1;
			printf(" DEBUG ON - LEVEL 1 \n");
		}
		else if (*argv[2] == '2') {
			DEBUG = 2;
			printf(" DEBUG ON \n");
		}
		else if (*argv[2] == '3') {
			DEBUG = 3;
			printf(" DEBUG with mem dump ON \n");
		}
	}
	//printf("You wrote %s \n\n", argv[1]);
	char *fileLocation = argv[1];
	FILE *ardealFile = fopen(fileLocation, "r");

	if (ardealFile == NULL) {
		printf("\n No focare! \n");
		printf("[EN] Couldn't open the file. Is the file name correctly written? \n");
		printf("[RO] Nu s-a putut deschide fisierul. Ati dat numele corect al fisierului? \n");
		printf("[ARDEAL] Tulai doamne ma dapu nu putui deschide fisieru ala! Iscalitul-ai bine?  \n");
		return -1;
	}

	//check file size and allocate code array
	fseek(ardealFile, 0L, SEEK_END);
	int eof = ftell(ardealFile);
	rewind(ardealFile);
	//malloc and initialize code buffer
	codeArray = malloc(sizeof(char) * (eof + 1));
	codeArray[0] = '\0';

	if (DEBUG > 0) {
		printf("Size of file: %d \n", eof);
	}


	int currentLine = 0;
	int lineBufferLength = 0;
	while (fgets(lineBuffer, 300, ardealFile) != NULL)
	{
		currentLine++;

		lineBufferLength = strlen(lineBuffer);
		if (DEBUG > 0) {
			printf("Line nr. [%d], Size of line [%d] | %s", currentLine, strlen(lineBuffer), lineBuffer);
		}

		//check line for possible syntax errors
		int clbIndex = 0;
		int wbIndex = 0;
		while (lineBuffer[clbIndex] != '\n') {
			if (lineBuffer[clbIndex] != ' ') {
				wordBuffer[wbIndex] = lineBuffer[clbIndex];
				wbIndex++;
				if (wbIndex > 10) {
					printf("Syntax error at line %d: '%s' is not a valid command and command buffer size (normally 2) is ridiculously exceeded :)", currentLine, wordBuffer);
					return -1;
				}
			}
			else {
				//add null terminator to end and check word and reset wordBuffer index to 0
				wordBuffer[wbIndex + 1] = '\0';
				if (!checkWord(wordBuffer)) {
					printf("Syntax error at line %d: '%s' is not a valid command! \n", currentLine, wordBuffer);
					return -1;
				}
				wbIndex = 0;
			}
			clbIndex++;
		}
		// check complete, if no errors until now it means the code is at least syntactically correct
		// make sure to change the endline char with a space
		if (lineBufferLength > 0 && lineBuffer[lineBufferLength - 1] == '\n') lineBuffer[lineBufferLength - 1] = ' ';
		//copy this line to the code array
		strcat(codeArray, lineBuffer);
		// process buffer
	}

	if (DEBUG > 0) {
		printf("\n This is the whole code array buffer: %s \n Starting program execution... \n", codeArray);
	}
	executeArdealCode(codeArray);
	fclose(ardealFile);

	printf("\n");
	system("PAUSE");
	return 0;
}

bool checkWord(char *currentWord) {

	//printf("Current word: %s", currentWord);

	if (strlen(currentWord) != 2) {
		return false;
	}
	if (strcmp(currentWord, NO) == 0) { return true; }
	else if (strcmp(currentWord, NI) == 0) { return true; }
	else if (strcmp(currentWord, MA) == 0) { return true; }
	else if (strcmp(currentWord, TU) == 0) { return true; }
	else if (strcmp(currentWord, LA) == 0) { return true; }
	else if (strcmp(currentWord, EL) == 0) { return true; }
	else if (strcmp(currentWord, CE) == 0) { return true; }
	else if (strcmp(currentWord, BE) == 0) { return true; }
	return false;
}

int executeWord(char *ardealWord) {
	if (checkWord(ardealWord)) {

		if (strcmp(ardealWord, MA) == 0) {
			++ptr;
			if (DEBUG == 2) {
				printf("ma: ++ptr, current val: %d \n", ptr);
			}
			else if (DEBUG > 2) {
				printf("ma: ++ptr, current val: %d \n", ptr);
				memDump(0, 9);
				system("PAUSE");
			}
		}

		if (strcmp(ardealWord, LA) == 0) {
			--ptr;
			if (ptr < programArray) {
				printf("\n [ERROR] Oh no! Drank too much palinca? Buffer overflow!");
				return -1;
			}
			if (DEBUG == 2) {
				printf("la: --ptr, current val: %d \n", ptr);
			}
			else if (DEBUG > 2) {
				printf("la: --ptr, current val: %d \n", ptr);
				memDump(0, 9);
				system("PAUSE");
			}
		}

		if (strcmp(ardealWord, TU) == 0) {
			++*ptr;
			if (DEBUG == 2) {
				printf("tu: ++*ptr, current val: %d \n", *ptr);
			}
			else if (DEBUG > 2) {
				printf("tu: ++*ptr, current val: %d \n", ptr);
				memDump(0, 9);
				system("PAUSE");
			}

		}

		if (strcmp(ardealWord, NI) == 0) {
			--*ptr;
			if (DEBUG == 2) {
				printf("ni: --*ptr, current val: %d \n", *ptr);
			}
			else if (DEBUG > 2) {
				printf("ni: --*ptr, current val: %d \n", ptr);
				memDump(0, 9);
				system("PAUSE");
			}
		}

		if (strcmp(ardealWord, BE) == 0) {
			putchar(*ptr);
		}

		if (strcmp(ardealWord, CE) == 0) {
			*ptr = getchar();
		}


		if (strcmp(ardealWord, NO) == 0) {
			//loop handling: each loop is extracted as a sub-array 
			//of the code array (search for last 'EL' - loop terminator) and run with executeArdealCode()
			//nested loops are treated recursively
			//to search for last 'EL'(loop terminator), start from end of the code array
			//loop is handled in executeArdealCode() when this function (executeWord()) returns 0;
			return 0;
		}

		if (strcmp(ardealWord, EL) == 0) {
			//do nothing, this is a loop terminator
		}
	}
	else {
		printf("[ERROR] Word '%s' is not a valid command \n", ardealWord);
	}

	return 1;
}

void executeArdealCode(char *ardealCodeArray) {

	int acaIndx = 0;
	int wbIndx = 0;
	while (ardealCodeArray[acaIndx] != '\0') {
		if (ardealCodeArray[acaIndx] != ' ') {
			wordBuffer[wbIndx] = ardealCodeArray[acaIndx];
			wbIndx++;
		}
		else {
			//if it is a space, make sure to ignore if it's the first space in the code array
			//also ignore if the last character was still a space
			if (acaIndx != 0 || ardealCodeArray[acaIndx-1] == ' ') {
				wordBuffer[wbIndx + 1] = '\0';

				//if executeWord not 1 => loop word(ni) detected
				if (!executeWord(wordBuffer)) {
					int loopTerminatorPosition = findLastLoopTerminator(ardealCodeArray, acaIndx);
					char *subCodeArray = malloc(sizeof(char) * (loopTerminatorPosition - acaIndx + 1));
					if (DEBUG > 0) { printf(" Allocated %d chars subCodeArray, LoopTerminator Pos: %d, codeArray index: %d \n", loopTerminatorPosition - acaIndx + 1, loopTerminatorPosition, acaIndx); }
					//copy loop code into subCodeArray
					strncpy(subCodeArray, ardealCodeArray + acaIndx, loopTerminatorPosition - acaIndx - 1);
					subCodeArray[loopTerminatorPosition - acaIndx - 1] = '\0';
					//recursively call executeArdealCode on subCodeArray
					while (*ptr != 0) {
						executeArdealCode(subCodeArray);
					}
					free(subCodeArray);

					//set next codeArray index to after the last loop terminator
					acaIndx = loopTerminatorPosition + 1;
				}
				wbIndx = 0;
			}
		}
		acaIndx++;
	}

}

int findLastLoopTerminator(char *ardealCodeArray, int currentPos) {
	int arrayIndx = strlen(ardealCodeArray);

	for (arrayIndx; currentPos < arrayIndx; arrayIndx--) {
		if (ardealCodeArray[arrayIndx] != ' ' && (ardealCodeArray[arrayIndx] == 'l' && ardealCodeArray[arrayIndx - 1] == 'e')) {
			return arrayIndx;
		}
	}
	return -1;
}

void memDump(int low, int high) {

	for (int i = low; i <= high; i++) {
		if (&programArray[i] == ptr) {
			printf("| <%d> ", programArray[i]);
		}
		else {
			printf("| %d ", programArray[i]);
		}

		if (i == high) {
			printf("| \n");
		}
	}

}