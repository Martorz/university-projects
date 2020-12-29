#include <stdlib.h>
#include <stddef.h>


struct list {
	int x;
	struct list* next;
};

void insertLast(struct list** h, int data) {

	struct list *link = calloc(1, sizeof(struct list*));

	link->x = data;

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

int getByIndex(struct list* h, size_t idx){
	size_t k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	return h->x;
}

void insertByIndex(struct list* h, size_t idx, int data){
	size_t k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	h->x = data;
}

void removeNode(struct list** changeableHead, struct list* h, size_t index){
	size_t k = 0;
	struct list *previous = NULL;
	if (index == 0) {
		*changeableHead = h->next;
	}
	else {
		for (k = 0; k < index; k++){
			previous = h;
			h = h->next;
		}
		previous->next = h->next;
	}
	free(h);
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
