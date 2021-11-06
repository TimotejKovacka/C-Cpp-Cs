/*
    Timotej Kovacka, 2478424k, SP Exercise 1a
    This is my own work as defined in the Academic Ethics agreement I have signed
*/

#include "date.h"
#include "tldlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tldnode{
    char* tldname;
    long count;
    struct tldnode* left, * right;
};

typedef struct SNode {
    TLDNode* data;
    struct SNode* previous;
} SNode;

struct tldlist {
	Date* begin;
	Date* end;
	TLDNode* root;
    long count;
};

struct tlditerator {
    SNode* stack;
    TLDNode* root;
};

TLDNode* newNode(char* tldname) {
    TLDNode* temp = (TLDNode*)malloc(sizeof(TLDNode));
    if (!temp) return NULL;
    temp->tldname = malloc(strlen(tldname) + 1);
    if (!(temp->tldname)) return NULL;
    strcpy(temp->tldname, tldname);
    temp->count = 1;
    temp->left = temp->right = NULL;
    return temp;
};

TLDNode* insert(TLDNode* node, char* tldname) {
    if (!node) return newNode(tldname);
    int cmp = strcmp(tldname, node->tldname);
    if (cmp < 0) {
        node->left = insert(node->left, tldname);
        if (!(node->left)) return NULL;
    }
    else if (cmp > 0) {
        node->right = insert(node->right, tldname);
        if (!(node->right)) return NULL;
    }
    else {
        node->count++;
    }
    return node;
};

int tldlist_add(TLDList* tld, char* hostname, Date* d) {
    if (date_compare(d, tld->begin) < 0 && date_compare(d, tld->end) > 0) return 0;
    char* tldname = strtok(strrchr(hostname, '.'), ".");
    if (!tld->root) {
        tld->root = newNode(tldname);
        tld->count++;
        return 1;
    }
    if (insert(tld->root, tldname) != NULL) {
        tld->count++;
        return 1;
    }
    return 0;
};

TLDList* tldlist_create(Date* begin, Date* end) {
	TLDList* temp = (TLDList*)malloc(sizeof(TLDList));
    if (!temp) return NULL;
	temp->begin = begin;
	temp->end = end;
	temp->root = NULL;
    temp->count = 0;
	return temp;
};

void freeTree(TLDNode* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node->tldname);
    free(node);
};

void tldlist_destroy(TLDList* tld) {
    freeTree(tld->root);
    free(tld);
};

long tldlist_count(TLDList* tld) {
    return tld->count;
};

SNode* newStackNode(TLDNode* node) {
    SNode* stackNode = (SNode*)malloc(sizeof(SNode));
    if (!stackNode) return NULL;
    stackNode->data = node;
    stackNode->previous = NULL;
    return stackNode;
};

int isStackEmpty(SNode* node) {
    return !node->previous;
};

SNode* push(SNode* root, TLDNode* node) {
    SNode* stackNode = newStackNode(node);
    stackNode->previous = root;
    return stackNode;
};

TLDNode* pop(SNode** root) {
    if (isStackEmpty(*root)) return NULL;
    SNode* temp = *root;
    *root = (*root)->previous;
    TLDNode* popped = temp->data;
    free(temp);
    return popped;
};

SNode* addLeftSubTree(TLDIterator* iter) {
    if (iter->root != NULL) {
        iter->stack = push(iter->stack, iter->root);
        iter->root = iter->root->left;
        return addLeftSubTree(iter);
    }
    return iter->stack;
}

TLDIterator* tldlist_iter_create(TLDList* tld) {
    TLDIterator* iterator = (TLDIterator*)malloc(sizeof(TLDIterator));
    if (!iterator) return NULL;
    iterator->stack = newStackNode(NULL);
    iterator->root = tld->root;
    iterator->stack = addLeftSubTree(iterator);
    return iterator;
};

TLDNode* tldlist_iter_next(TLDIterator* iter) {
    TLDNode* temp = pop(&(iter->stack));
    if (!temp) return NULL;
    iter->root = temp;
    if (temp->right) {
        iter->root = iter->root->right;
        iter->stack = addLeftSubTree(iter);
    }
    return temp;
};

void tldlist_iter_destroy(TLDIterator* iter) {
    while (pop(&(iter->stack)) != NULL);
    free(iter->stack);
    free(iter);
};

char* tldnode_tldname(TLDNode* node) {
    return node->tldname;
};

long tldnode_count(TLDNode* node) {
    return node->count;
};