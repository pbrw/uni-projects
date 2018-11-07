#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

#include "ListOfMovies.h"
#include "tools.h"


void addMovieToList(ListOfMovies list, int newMovieRating) {
    if (list->right->rating <= newMovieRating) {
        ListOfMovies newMovie = (ListOfMovies)mallocSafe(sizeof(struct Movie)); 
        
        newMovie->rating = newMovieRating;
        newMovie->left = list;
        newMovie->right = list->right;
        list->right->left = newMovie;
        list->right = newMovie;
    }
    else {
        addMovieToList(list->right, newMovieRating);
    }
}

void freeListOfMovies(ListOfMovies list) {
    if (!isEndOfList(list)) 
        freeListOfMovies(list->right);
    free(list); 
}

void printMovies(ListOfMovies list) {
    printf("%d", list->rating);
    
    if (!isEndOfList(list->right)) {
        printf(" ");
        printMovies(list->right);
    }
}

void cutUpToBestK(ListOfMovies list, int k) {
    if (k == -1) {
        freeListOfMovies(list->right);
        list->rating = -1;
        list->right = NULL;
    }
    else {
        if (!isEndOfList(list->right))
            cutUpToBestK(list->right, --k);
    }
}

void mergeListsOfMovies(ListOfMovies listA, ListOfMovies listB) {
    listA = listA->right;
    listB = listB->right;
     
    while (!isEndOfList(listA) || !isEndOfList(listB)) {
        if (listA->rating >= listB->rating) {
            listA = listA->right;   
        }
        else {
            ListOfMovies pointer = listB;
            
            listB = listB->right;
            pointer->left->right = pointer->right;
            pointer->right->left = pointer->left;
            listA->left->right= pointer;
            pointer->left = listA->left;
            pointer->right = listA;
            listA->left = pointer;
        }
    }
    freeListOfMovies(listB->left);
} 

void deleteMovieFromList(ListOfMovies list, int movieRating) {
    if (list->rating == movieRating && !isBeginOfList(list)) {
        list->left->right = list->right;
        list->right->left = list->left;
        free(list);
    }
    else {
        deleteMovieFromList(list->right, movieRating);
    }
}

void deleteRepetitions(ListOfMovies list) {
    list = list->right;
    
    while (!isEndOfList(list)) {
        if (list->rating == list->right->rating) {
            list->left->right = list->right;
            list->right->left = list->left;
            
            ListOfMovies tmp = list;
            list = list->right;
            free(tmp);
        }
        else {
            list = list->right;
        }
    }
}

ListOfMovies giveNewListOfMovies() {
    ListOfMovies leftGuard = (ListOfMovies)mallocSafe(sizeof(struct Movie));
    ListOfMovies rightGuard = (ListOfMovies)mallocSafe(sizeof(struct Movie));
    
    leftGuard->rating = MAX_INT;
    rightGuard->rating = -1;
    leftGuard->left = NULL;
    rightGuard->right = NULL;
    leftGuard->right = rightGuard;
    rightGuard->left = leftGuard;
    
    return leftGuard;
}

ListOfMovies copyUpToKGreaterThanM(ListOfMovies list, int k, int m) {
    ListOfMovies result = giveNewListOfMovies();
    ListOfMovies pointer = result->right;
    
    list = list->right;
    
    while (!isEndOfList(list) && k > 0 && list->rating > m) {
        ListOfMovies copy = (ListOfMovies)mallocSafe(sizeof(struct Movie));
        
        copy->rating = list->rating;
        copy->right = pointer;
        copy->left = pointer->left;
        pointer->left->right = copy;
        pointer->left = copy; 
        
        k--;    
        list = list->right;
    }
    
    return result;
}

int giveBestRating(ListOfMovies list) {
    if (isEmptyListOfMovies(list))
        return -1;
    else 
        return list->right->rating;
}

bool isInListOfMovies(ListOfMovies list, int movieRating) {
    if(list->rating == movieRating && !isBeginOfList(list))
        return true;
    else if (isEndOfList(list))
        return false;
    else 
        return isInListOfMovies(list->right, movieRating);
}

bool isEmptyListOfMovies(ListOfMovies list) {
    return list->right->rating == -1;
}


bool isEndOfList(struct Movie *ptr) {
    return ptr->rating == -1;
}

bool isBeginOfList(struct Movie *ptr) {
    return ptr->left == NULL;
}
