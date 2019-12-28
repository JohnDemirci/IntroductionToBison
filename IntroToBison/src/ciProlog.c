
/**
* Name: Umit Demirci
* Lab: Lab 8 Introduction to Bison
* Date: 10/29/2019
**/

#include "ciProlog.h"

// the knowledge base
// a linked list of propositions
// if a proposition is on the list, it is assumed to be true
// anything not on the list is false
// the first element is empty; it is used as an anchor for kb_head and kb_tail
// we always add at kb_tail
// we always search from kb_head->next;

PROP_TYPE *kb_head, *kb_tail;

void initKnowledgeBase(void)
{
    kb_head = kb_tail = (PROP_TYPE *) malloc(sizeof(PROP_TYPE)); // always empty head of the list
    kb_head->name = ""; // indicates the empty head; skip in searches
    kb_head->next = NULL;
}

void yyerror(char *s)
{
    fprintf(stderr, "yyerror: %s\n", s);
}

// returns negation of input
bool not(bool logexpr1)
{
    // TODO implement the function
    if (logexpr1 == false) {
        return true;
    }
    return false;
}

// logical and...
bool and(bool logexpr1, bool logexpr2)
{
    // TODO implement the function
    if ((logexpr1 == true) && (logexpr2 == true)) {
        return true;
    }
    return false;
}

// logical or...
bool or(bool logexpr1, bool logexpr2)
{
    // TODO implement the function

    if ((logexpr1 == true) || (logexpr2 == true)) {
        return true;
    }
    return false;
}

// Check if the proposition is in the database.
// If it is already there, return false.
// If it is not already there, add it to the database and return true.
bool assert(char *proposition)
{
    // TODO implement the function

    int res = strcmp(kb_head->name, "");
    if ((res == 0) && (kb_head->next == NULL)) {
        // adding
        kb_head->name = malloc(sizeof(proposition));
        PROP_TYPE *temp = (PROP_TYPE*) malloc(sizeof(PROP_TYPE));
        temp->name = malloc(sizeof(proposition));
        // strcpy(kb_head->name, proposition);
        strcpy(temp->name, proposition);
        temp->next = kb_head;
        kb_head = temp;
        return true;
    }
    if (!eval(proposition)) {
        PROP_TYPE *temp = (PROP_TYPE*) malloc(sizeof(PROP_TYPE));
        temp->name = malloc(sizeof(proposition));
        strcpy(temp->name, proposition);
        temp->next = kb_head;
        kb_head = temp;
        return true;
    }
    return false;
}



// Search the database for the proposition.
// If it is in the database, remove it from the database and return true.
// If it is not in the database, return false.
bool retract(char *proposition)
{
    // TODO implement the function
    int res = strcmp(kb_head->name, "");
    if ((res == 0) && (kb_head->next == NULL)) {
        return false;
    }
    if (proposition == NULL) {
        return false;
    }
    if (eval(proposition)) {
        if (strcmp(kb_head->name, proposition) == 0) {
            PROP_TYPE *newhead = kb_head->next;
            free(kb_head->name);
            free(kb_head);
            kb_head = newhead;
            if (kb_head == NULL) {
                printf("soemthing happened\n");
            }
            return true;
        }
        PROP_TYPE *prevNode, *currNode;
        prevNode = kb_head;
        currNode = kb_head->next;
        while (currNode != NULL) {
            if (strcmp(currNode->name, proposition) == 0) {
                prevNode->next = currNode->next;
                if (strcmp(currNode->name, kb_tail->name) == 0) {
                    kb_tail = prevNode;
                }
                free(currNode->name);
                free(currNode);
            }
            currNode = currNode->next;
            prevNode = prevNode->next;
        }
        return true;
    }
    return false;
}

// Find the proposition in the knowledge base.
// If found, return true.
// Otherwise, return false.
bool eval(char *proposition)
{
    // TODO implement the function

    if (kb_head->next == NULL) {
        return  false;
    }

    if (proposition == NULL) {
        return false;
    }


    int j = strcmp(kb_head->name, "");
    if (j == 0) {
        return false;
    }

    PROP_TYPE  *temp = kb_head;
    while (temp != NULL) {
        int res = strcmp(temp->name,proposition);
        if (res == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
};
