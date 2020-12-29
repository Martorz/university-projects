#ifndef TREE_H
#define TREE_H

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
} node;

node * addNode (node * root, int data);

void printPrefix(node* root, size_t tabsNum);

void clearTree(node * root);

node * linkedListIntoAVL(struct list * head, size_t length);

#endif
