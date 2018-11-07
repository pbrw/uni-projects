#include <stdbool.h>

#define MAX_USER_ID 65535

//List of pointers to users who are children of some user.
//Empty list is [-1] for convenience
//Leftmost child's pointer points to the rightmost child and vice versa (cyclic list)
typedef struct Child *ListOfChildren;

//Represents that [*userPtr] is a child in the list of children 
//of some other user. 
struct Child {
    struct User *userPtr;
    ListOfChildren left, right;
};

//PointerToUser[userId] is a pointer to child in the list which 
//points to [userId]. Needed to delete user fast.
struct Child *pointerToUser[MAX_USER_ID + 1];   

//Returns new empty list of children [-1]. Complexity O(1)
ListOfChildren giveNewListOfChildren();

//Adds a child to [list] which will point to [childUser]. Complexity O(1)
struct Child * addChildToList(ListOfChildren list, struct User *childUser);

//Pastes [list] in place of [*ptr] child. [*ptr] is deleted, [list] is deleted.
//Needed to delete user. Complexity O(1)
void insertListIntoList (struct Child *ptr, ListOfChildren list);

//Frees memory allocated for [list]. Complexity O(|list|)
void freeListOfChildren(ListOfChildren list);

//Tests if [list] is empty. Complexity O(1)
bool isEmptyListOfChildren(ListOfChildren list);
