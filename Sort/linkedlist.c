#include <stdlib.h>
#include <stddef.h>

struct list {
	double x;
	struct list* next;
};

void insertLast(double data) {

	struct list *link = calloc(1, sizeof(struct list*));

	link->x = data;

   	if (firstItems != NULL){
		struct list* findLast = firstItems;
		while (findLast->next != NULL) {
	   		findLast = findLast->next;
		}
		findLast->next = link;
	}
	else {
		firstItems = link;
	}
}

double getByIndex(struct list* h, size_t idx){
	int k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	return h->x;
}

void insertByIndex(struct list* h, size_t idx, double data){
	int k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	h->x = data;
}

void removeNode(struct list* h, size_t index){
	int k = 0;
	struct list *previous = NULL;
	if (index == 0) {
		firstItems = h->next;
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