#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

#include "ListOfChildren.h"
#include "tools.h"

ListOfChildren giveNewListOfChildren() {
    ListOfChildren new = (ListOfChildren)mallocSafe(sizeof(struct Child));
    
    new->userPtr = NULL;
    new->left = new;
    new->right = new;
    
    return new;
}

struct Child * addChildToList(ListOfChildren list, struct User *childUser) {
    struct Child * new = (struct Child *)mallocSafe(sizeof(struct Child));
    
    new->userPtr = childUser;
    new->left = list;
    new->right = list->right;
    if (list->left == list)
        list->left = new;
    list->right->left = new;
    list->right = new;
    
    return new;
}

void insertListIntoList (struct Child *ptr, ListOfChildren list) {
    if (isEmptyListOfChildren(list)) {
        ptr->left->right = ptr->right;
        ptr->right->left = ptr->left;
    }
    else {
        ptr->left->right = list->right;
        ptr->right->left = list->left;
        list->right->left = ptr->left;
        list->left->right = ptr->right;
    }
    
    free(list);
    free(ptr);
}

void freeListOfChildren(ListOfChildren list) {
    if (list->right->userPtr != NULL)freeListOfChildren(list->right);
    free(list);
}

bool isEmptyListOfChildren(ListOfChildren list) {
    return list->right == list;
}

