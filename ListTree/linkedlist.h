#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct list {
	int x;
	struct list* next;
};

void insertLast(struct list** h, int data);

int getByIndex(struct list* h, size_t idx);

void insertByIndex(struct list* h, size_t idx, int data);

void removeNode(struct list** changeableHead, struct list* h, size_t index);

size_t findMinItemID(struct list * arr);

size_t findMaxItemID(struct list * arr);

void clearList(struct list * arr);

#endif
