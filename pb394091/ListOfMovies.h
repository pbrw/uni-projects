#include <stdbool.h>
#include <stdlib.h> 

#define MAX_INT 2147483647

//Bidirectional list of movies sorted in descending order
//Empty list is [MAX_INT; -1] for convenience
typedef struct Movie *ListOfMovies;

//Represents a single movie in the list
struct Movie {
    int rating;
    ListOfMovies left, right;
};

// |list| - number of elements in list

//Adds movie with [newMovieRating] to the list keeping it
//sorted in descending order. Complexity O(|list|)
void addMovieToList(ListOfMovies list, int newMovieRating);

//Frees memory allocated for [list]. Complexity O(|list|)
void freeListOfMovies(ListOfMovies list);

//Prints movies' ratings with spaces only between them. Complexity O(|list|)
void printMovies(ListOfMovies list);

//Leaves only best [k] movies in the [list] or all of them
//if there are fewer than [k] initially. Rest is deleted.
//Complexity O(|list|)
void cutUpToBestK(ListOfMovies list, int k);

//Merges two lists and keeps them sorted. Complexity O(|listA| + |listB|)
void mergeListsOfMovies(ListOfMovies listA, ListOfMovies listB);

//Deletes movie from list. Complexity O(|list|)
void deleteMovieFromList(ListOfMovies list, int movieRating);

//Deletes repetition in the list. Complexity O(|list|)
void deleteRepetitions(ListOfMovies list);

//Returns new empty list of movies [MAX_INT, -1]. Complexity O(1) 
ListOfMovies giveNewListOfMovies();

//Returns new sorted list containing up to [k] best movies from
//the [list] which rating is bigger than [m]. [list] is left unchanged.
//Complexity O(k)
ListOfMovies copyUpToKGreaterThanM(ListOfMovies list, int k, int m);

//Returns the best rating of movie from [list]. If [list] is empty returns -1
//Complexity O(1)
int giveBestRating(ListOfMovies list);

//Tests if [movieRating] is in the [list]. Complexity O(|list|)
bool isInListOfMovies(ListOfMovies list, int movieRating);

//Tests if [list] is empty. Complexity O(1)
bool isEmptyListOfMovies(ListOfMovies list);

//Test if [ptr] points to the last element in the list. Complexity O(1)
bool isEndOfList(struct Movie *ptr);

//Test if [ptr] points to the first element in the list. Complexity O(1)
bool isBeginOfList(struct Movie *ptr);
