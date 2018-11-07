#include <stdio.h>

#include "InputReading.h"

char addUserCommand[] = "addUser_";
char delUserCommand[] = "delUser_";
char addMovieCommand[] = "addMovie_";
char delMovieCommand[] = "delMovie_";
char marathonCommand[] = "marathon_";

bool isMatchingCommand(char *command, char *text) {
    while (*command != '_') {
        if (*command != *text)
            return false;
        ++command;
        ++text;
    }
    
    if (*text != (char)(0))
        return false;
    
    return true;
}

bool isEndOfLine() {
    int character;
    character = getchar();
    return (character == (int)'\n');
}

void readRestOfLine() {
    int character;
    do {
        character = getchar();
    }while (character != (int)'\n');
}
