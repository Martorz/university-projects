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
	/*else {
		for (size_t i = 0; i < tabsNum; i++) {
			printf("\t");
		}
		printf("\\_ ");
		printf("NULL\n");
	}*/
}

void clearTree(node * root) {
	if(root != NULL)
    {
        clearTree(root->left);
        clearTree(root->right);
        free(root);
    }
}

node * vineIntoAVL2(node * root) {
	node * currentNode = root;
	node * rootCopy = NULL;
	node * previous = NULL;
	size_t count = 0;

	/*previous = currentNode;
	currentNode = currentNode->left;
	previous->left = NULL;
	root = currentNode;
	currentNode->right = previous;
	printPrefix(root, 0);
	printf("\n");
	currentNode = currentNode->left;
	
	previous = currentNode;
	currentNode = currentNode->left;
	previous->left = NULL;
	root->left = currentNode;
	currentNode->right = previous;
	printPrefix(root, 0);
	printf("\n");
	currentNode = currentNode->left;
	rootCopy = root->left;

	previous = currentNode;
	currentNode = currentNode->left;
	previous->left = NULL;
	rootCopy->left = currentNode;
	currentNode->right = previous;
	printPrefix(root, 0);
	printf("\n");*/
	for (int i = 0; i < 3; i++) {
	while (currentNode != NULL && currentNode->left != NULL) {
		previous = currentNode;
		currentNode = currentNode->left;
		previous->left = NULL;
		if (count == 0){
			root = currentNode;
			rootCopy = root;
			count++;
		}
		else {
			rootCopy->left = currentNode;
			rootCopy = rootCopy->left;
		}

		if (i != 0) {
			previous->left = currentNode->right;
		}
		currentNode->right = previous;
		currentNode = currentNode->left;
	
		printPrefix(root, 0);
		printf("-------------------\n");

	}

	currentNode = root;
	rootCopy = NULL;
	previous = NULL;
	count = 0;
	}

	/*previous = currentNode;
	currentNode = currentNode->left;
	previous->left = NULL;
	root = currentNode;
	previous->left = currentNode->right;
	currentNode->right = previous;
	printPrefix(root, 0);
	printf("\n");
	currentNode = currentNode->left;

	previous = currentNode;
	currentNode = currentNode->left;
	previous->left = NULL;
	root->left = currentNode;
	previous->left = currentNode->right;
	currentNode->right = previous;
	printPrefix(root, 0);
	printf("\n");
	currentNode = currentNode->left;
	rootCopy = root->left;*/

	//printPrefix(root, 0);
	return rootCopy;
}

node * reverse(node * root, size_t nodeNum) {
	node * currentNode = root;
	node * previous = NULL;
	for (int i = 0; i < nodeNum - 1; i++) {
		previous = currentNode;
		currentNode = currentNode->right;
		previous->right = NULL;
		currentNode->left = previous;
	}
	currentNode->right = NULL;
	//printPrefix(currentNode, 0);
	return currentNode;
}

node * vineIntoAVL(node * root, size_t vineLen) {
	size_t halfVineLen = vineLen / 2;
	if (vineLen % 2 == 0) {
		halfVineLen--;
	}
	node * currentNode = root;

	for (int i = 0; i < halfVineLen; i++) {
		currentNode = currentNode->right;
	}

	if (halfVineLen > 1) { 
		currentNode->left = reverse(root, halfVineLen);
		currentNode->right = vineIntoAVL(currentNode->right, halfVineLen);
		currentNode->left = vineIntoAVL(currentNode->left, halfVineLen);
		
	}	

	return currentNode;
}

node * linkedListIntoVine(struct list * head, node * root) {
	/*
		List has to be sorted, contain int numbers, head is the smallest number
	*/

	while (head != NULL) {
		root = addNode(root, head->x);
		head = head->next;
	}

	return root;
}