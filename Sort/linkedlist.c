#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>


struct list {
	double x;
	struct list* next;
};

void insertLast(struct list** h, double data) {

	struct list *link = calloc(1, sizeof(*link));
	link->x = data;
	link->next = NULL;

   	if (*h != NULL){
		struct list* findLast = *h;
		while (findLast->next != NULL) {
	   		findLast = findLast->next;
		}
		findLast->next = link;
	}
	else {
		*h = link;
	}
}

void printList(struct list* h){
	printf("%lf \n", h->x);
	while (h->next != NULL){
		h = h->next;
		printf("%lf \n", h->x);
	}
}

double getByIndex(struct list* h, size_t idx){
	size_t k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	return h->x;
}

void insertByIndex(struct list* h, size_t idx, double data){
	size_t k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	h->x = data;
}

void removeNode(struct list** h, size_t index){
	size_t k = 0;
	struct list* currentNode = *h;
	struct list *previous = NULL;
	if (index == 0) {
		*h = currentNode->next;
	}
	else {
		for (k = 0; k < index; k++){
			previous = currentNode;
			currentNode = currentNode->next;
		}
		previous->next = currentNode->next;
	}
	free(currentNode);
}

size_t findMinItemID(struct list * arr) {
	size_t itemID = 0;
	size_t counter = 0;
	double itemValue = getByIndex(arr, itemID);
	while (arr != NULL) {
		if (arr->x < itemValue) {
			itemValue = arr->x;
			itemID = counter;
		}
		counter++;
		arr = arr->next;
	}
	return itemID;
}

size_t findMaxItemID(struct list * arr) {
	
	size_t itemID = 0;
	size_t counter = 0;
	double itemValue = getByIndex(arr, itemID);
	while (arr != NULL) {
		if (arr->x > itemValue) {
			itemValue = arr->x;
			itemID = counter;
		}
		counter++;
		arr = arr->next;
	}
	return itemID;
}

void clearList(struct list * arr){
	if (arr == NULL) {
		return;
	}
	clearList(arr->next);
	free(arr);
}
