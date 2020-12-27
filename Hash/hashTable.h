#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 100

struct dataStruct{
	int height;
	int weight;
};

struct person{
	char * name;
	struct dataStruct data;
};

void initHashTable(struct person ** hashTable);

void printTable(struct person ** hashTable);

int hashTableInsert(struct person ** hashTable, char * name, int height, int weight);

struct person * hashTableFind (struct person ** hashTable, char * name);

void hashTableClear(struct person ** hashTable);

#endif