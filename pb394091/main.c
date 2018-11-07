#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

#include "ListOfMovies.h"
#include "ListOfChildren.h"
#include "InputReading.h"
#include "tools.h"

//Represents a single user. Contains id number, list of movies he recommends
//sorted in descending order and list of his children in the tree
struct User {
    int id;
    ListOfMovies movies;
    ListOfChildren children;
};

//Tests if user is currently present in the tree. Complexity O(1)
bool isPresent(int userId) {
    return pointerToUser[userId] != NULL;
}

//Adds new user if doesn't exist, otherwise prints ERROR
//adds new child to the [userId]'s list of children. 
void addUser(int parentUserId, int userId) {
    if (!isPresent(parentUserId) || isPresent(userId)) {
        fprintf( stderr, "ERROR\n" );
    }
    else {
        struct User *ptr = pointerToUser[parentUserId]->userPtr;
        struct User *new = (struct User *)mallocSafe(sizeof(struct User));
        
        new->id = userId;
        new->children = giveNewListOfChildren();
        new->movies = giveNewListOfMovies();
        
        pointerToUser[userId] = addChildToList(ptr->children, new); 
        
        printf( "OK\n" );
    }
}

//Deletes user if exists. 
//Inserts list of [userId] children into [userId] parent's list of children.
void delUser(int userId) {
    if(!isPresent(userId)) {
        fprintf( stderr, "ERROR\n" );
    }
    else {
        struct Child *ptr = pointerToUser[userId];
        struct User *tmp = ptr->userPtr;
        
        insertListIntoList(ptr, ptr->userPtr->children);
        
        freeListOfMovies(tmp->movies);
        free(tmp);
        pointerToUser[userId] = NULL;
        
        printf( "OK\n" );
    }
} 

//Adds movie if doesn't exist.
void addMovie(int userId, int movieRating) {
    if (isPresent(userId)) {
        ListOfMovies currentMovies = pointerToUser[userId]->userPtr->movies;

        if (!isInListOfMovies(currentMovies, movieRating)) {
            addMovieToList(currentMovies, movieRating);
            printf( "OK\n" );
        }
        else {
            fprintf( stderr, "ERROR\n" );
        } 
    }
    else {
        fprintf( stderr, "ERROR\n" );
    }
}

//Deletes movie if exists.
void delMovie(int userId, int movieRating) {
    if (isPresent(userId)) {
        ListOfMovies currentMovies = pointerToUser[userId]->userPtr->movies;

        if (isInListOfMovies(currentMovies, movieRating)) {
            deleteMovieFromList(currentMovies, movieRating);
            printf( "OK\n" );
        }
        else {
            fprintf( stderr, "ERROR\n" );
        } 
    }
    else {
        fprintf( stderr, "ERROR\n" );
    }
}

//Computes the output for marathon function. Selects [user]'s best [k] movies 
//which have over [minimalRating] rating. Does it recursievely for the children,
//merges returned lists and returns final list of movies.
ListOfMovies selectMovies(struct User *user, int k, int minimalRating) {
    ListOfMovies result;
    result = copyUpToKGreaterThanM(user->movies, k, minimalRating);
    
    ListOfChildren iterator;
    iterator = user->children->right;
    
    int bestRating = giveBestRating(user->movies);
    ListOfMovies childMovies;
    struct User *child;

    while (iterator->userPtr != NULL) {
        child = iterator->userPtr;
        childMovies = selectMovies(child, k, max(minimalRating, bestRating));
        
        mergeListsOfMovies(result, childMovies);
        deleteRepetitions(result);
        cutUpToBestK(result, k);
        
        iterator = iterator->right;
    }
    
    return result;
}

//Selects best [k] movie recommendations among [userId]'s movies and
//his children according to the rules decribed in the statement 
void marathon(int userId, int k) {
    if (!isPresent(userId)) {
        fprintf(stderr, "ERROR\n");
    }
    else {
        ListOfMovies selectedMovies;
        selectedMovies = selectMovies(pointerToUser[userId]->userPtr, k, -1);
        
        if (!isEmptyListOfMovies(selectedMovies)) {
            printMovies(selectedMovies->right);
            printf("\n");
        }
        else {
            printf("NONE\n");
        }
        
        freeListOfMovies(selectedMovies);
    }
}

//Frees memory allocated for [user] and all of his children in the tree.
void freeTree(struct User *user) {
    ListOfChildren iterator = user->children->right;
    
    while (iterator->userPtr != NULL) {
        freeTree(iterator->userPtr);
        iterator = iterator->right;
    }
    
    freeListOfChildren(user->children);
    freeListOfMovies(user->movies);
    free(user);
}
int main() {
    //Adding initial userZero to the tree structure
    struct User *userZero = (struct User *)mallocSafe(sizeof(struct User));
        
    userZero->id = 0;
    userZero->children = giveNewListOfChildren();
    userZero->movies = giveNewListOfMovies();
    
    struct Child childUserZero;
    
    childUserZero.userPtr = userZero;
    pointerToUser[0] = &childUserZero;
    
    
    //Reading input
    long long argument1, argument2;
    
    while (scanf("%s", input) != EOF) { 
        //Checking if line is commented
        if (input[0] == '#') {
            readRestOfLine();
        }
        else {
            if (isEndOfLine()) {
                fprintf(stderr, "ERROR\n");
                continue;
            }
            if (scanf("%lld", &argument1) != 1) {
                fprintf(stderr, "ERROR\n");
                readRestOfLine();
                continue;
            }
            if (argument1 < 0 || argument1 > MAX_USER_ID) {
                fprintf(stderr, "ERROR\n");
                readRestOfLine();
                continue;
            }
            //Checking if addUser command occurs 
            if (isMatchingCommand(addUserCommand, input)) {
                if (isEndOfLine()) {
                    fprintf(stderr, "ERROR\n");
                    continue;
                }
                if (scanf("%lld", &argument2) != 1) {
                    fprintf(stderr, "ERROR\n");
                    readRestOfLine();
                    continue;
                }
                if (argument2 < 0 || argument2 > MAX_USER_ID) {
                    fprintf(stderr, "ERROR\n");
                    readRestOfLine();
                    continue;
                }
                if (!isEndOfLine()) {
                    readRestOfLine();
                    fprintf(stderr, "ERROR\n");
                    continue;
                }
                addUser(argument1, argument2);
            }
            //Checking if delUser command occurs
            else if (isMatchingCommand(delUserCommand, input)) {
                if (!isEndOfLine()) {
                    readRestOfLine();
                    fprintf(stderr, "ERROR\n");
                    continue;
                }
                if (argument1 == 0) {
                    fprintf(stderr, "ERROR\n" );
                    continue;
                }
                delUser(argument1);
            }
            //Checking if addMovie command occurs
            else if (isMatchingCommand(addMovieCommand, input)) {
                if (isEndOfLine()) {
                    fprintf(stderr, "ERROR\n");
                    continue;
                }
                if (scanf("%lld", &argument2) != 1) {
                    fprintf(stderr, "ERROR\n");
                    readRestOfLine();
                    continue;
                }
                if (argument2 < 0 || argument2 > MAX_INT) {
                    fprintf(stderr, "ERROR\n");
                    readRestOfLine();
                    continue;
                }
                if (!isEndOfLine()) {
                    readRestOfLine();
                    fprintf(stderr, "ERROR\n");
                    continue;
                }
                addMovie(argument1, argument2);
            }
            //Checking if delMovie command occurs
            else if (isMatchingCommand(delMovieCommand, input)) {
                if (isEndOfLine()) {
                    fprintf( stderr, "ERROR\n" );
                    continue;
                }
                if (scanf("%lld", &argument2) != 1) {
                    fprintf(stderr, "ERROR\n");
                    readRestOfLine();
                    continue;
                }
                if (argument2 < 0 || argument2 > MAX_INT) {
                    fprintf( stderr, "ERROR\n" );
                    readRestOfLine();
                    continue;
                }
                if (!isEndOfLine()) {
                    readRestOfLine();
                    fprintf( stderr, "ERROR\n" );
                    continue;
                }
                delMovie( argument1, argument2 );
                
            }
            //Checking if marathon command occurs
            else if(isMatchingCommand(marathonCommand, input)) {
                if (isEndOfLine()) {
                    fprintf( stderr, "ERROR\n" );
                    continue;
                }
                if (scanf("%lld", &argument2) != 1) {
                    fprintf(stderr, "ERROR\n");
                    readRestOfLine();
                    continue;
                }
                if (argument2 < 0 || argument2 > MAX_INT) {
                    fprintf(stderr, "ERROR\n");
                    readRestOfLine();
                    continue;
                }
                if (!isEndOfLine()) {
                    readRestOfLine();
                    fprintf(stderr, "ERROR\n");
                    continue;
                }
                marathon(argument1, argument2);
            }
            else {
                readRestOfLine();
                fprintf(stderr, "ERROR\n");
            }
        }
        for (int i = 0; i < 10; i++)input[i] = 0;
    }
    
    //Clearing memory
    freeTree(userZero);

    return 0;
}
