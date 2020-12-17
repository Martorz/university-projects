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

node * vineIntoAVL2(node * root);

node * vineIntoAVL(node * root, size_t vineLen);

node * linkedListIntoVine(struct list * head, node * root);

#endif
