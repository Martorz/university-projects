#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
} node;

node * createNode (int data) {
	node * newNode = (node*)malloc(sizeof(node));

	if (newNode == NULL) {
		printf("Error: Out of memory. Function name: createNode. File name: tree3.c\n");
		exit(-1);
	}

	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

node * addNode (node * root, int data) {
	if (root == NULL) {
		root = createNode(data);
	}
	else {
		int isLeft = 0;
		node * currentNode = root;
		node * previous = NULL;

		while (currentNode != NULL) {
			previous = currentNode;
            if(data < currentNode->data)
            {
                isLeft = 1;
                currentNode = currentNode->left;
            }
            else if(data >= currentNode->data)
            {
                isLeft = 0;
                currentNode = currentNode->right;
            }
		}

		if (isLeft == 1) {
            previous->left = createNode(data);
        }
        else {
            previous->right = createNode(data);
        }
	}

	return root;
}

void printPrefix(node* root, size_t tabsNum){
	if (root != NULL){
		for (size_t i = 0; i < tabsNum; i++) {
			printf("\t");
		}
		printf("\\_ ");
		printf("%d\n", root->data);
		printPrefix(root->left, tabsNum + 1);
		printPrefix(root->right, tabsNum + 1);
	}
}

void clearTree(node * root) {
	if(root != NULL)
    {
        clearTree(root->left);
        clearTree(root->right);
        free(root);
    }
}

node * linkedListIntoAVL(struct list * head, size_t length){
	if (head == NULL || length == 0){
		return NULL;
	}

	if (head->next == NULL) {
		node * root = NULL;
		root = createNode(head->x);
		return root;
	}

	size_t halfLen = length / 2;
	node * root = NULL;
	root = createNode(0);
	root->left = linkedListIntoAVL(head, halfLen);

	struct list * currentNode = head;
	for (size_t i = 0; i < halfLen; i++)
	{
		if (currentNode == NULL) {
			return NULL;
		}

		currentNode = currentNode->next;
	}

	root->data = currentNode->x;
	root->right = linkedListIntoAVL(currentNode->next, (length - 1) / 2);

	return root;
}