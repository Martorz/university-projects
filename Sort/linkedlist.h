#ifndef LINKEDLIST_H
#define LINKEDLIST_H


struct list;

void insertLast(struct list** h, double data);

double getByIndex(struct list* h, size_t idx);

void insertByIndex(struct list* h, size_t idx, double data);

void removeNode(struct list** changeableHead, struct list* h, size_t index);

size_t findMinItemID(struct list * arr);

size_t findMaxItemID(struct list * arr);

#endif
