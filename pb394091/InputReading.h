#include <stdbool.h>

//Input buffer
char input[1000];
char inputChar;

//Strings containing names of commands
char addUserCommand[8];
char delUserCommand[8];
char addMovieCommand[9];
char delMovieCommand[9];
char marathonCommand[9];

//Tests if [command] is the prefix of [text]. Complexity O(|command|)
bool isMatchingCommand(char *command, char *text);

//Tests if the next character in the input is '\n'. Complexity O(1)
bool isEndOfLine();

//Reads content of the line till the end. Complexity O(line length)
void readRestOfLine();
