#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME 255
#define TABLE_SIZE 10

struct dataStruct{
	int height;
	int weight;
};

struct person{
	char * name;
	struct dataStruct data;
	struct person * next;
};


unsigned int hash(char *name){
	int length = strnlen(name, MAX_NAME);
	unsigned int hashValue = 0;
	for (int i = 0; i < length; i++) {
		hashValue += name[i];
		hashValue = (hashValue * name[i]) % TABLE_SIZE;
	}

	return hashValue;
}

void initHashTable(struct person ** hashTable){
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable[i] = NULL;
	}
}

void printTable(struct person ** hashTable){
	for (int i = 0; i < TABLE_SIZE; i++){
		if (hashTable[i] == NULL){
			printf("\t%i\t---\n", i);
		}
		else {
			printf("\t%i\t%s", i, hashTable[i]->name);
			struct person * p = hashTable[i]->next;
			while (p != NULL){
				printf(" - %s", p->name);
				p = p->next;
			}
			printf("\n");
		}
	}
}

int hashTableInsert(struct person ** hashTable, char * name, int height, int weight){

	struct person * p = (struct person*)malloc(sizeof(*p));
	p->name = name;
	p->data.height = height;
	p->data.weight = weight;
	p->next = NULL;

	int index = hash(p->name);

	if (hashTable[index] != NULL) {
		p->next = hashTable[index];
		hashTable[index] = p; 
	}

	hashTable[index] = p;
	return 1;

}

struct person * hashTableFind (struct person ** hashTable, char * name) {
	int index = hash(name);

	if (hashTable[index] != NULL) {
		struct person * p = hashTable[index];
		while(p != NULL && strcmp(p->name, name) != 0) {
			p = p->next;
		}
		
		if (p == NULL) {
			return NULL;
		}
		else {
			return p;
		}		
	}
	else {
		return NULL;
	}
}

void hashTableClear(struct person ** hashTable){
	for(int i = 0; i < TABLE_SIZE; i++){
		struct person * p = hashTable[i];
		while (p != NULL){
			struct person * currentNode = p;
			p = p->next;
			free(currentNode->name);
			free(currentNode);
		}
		hashTable[i] = NULL;
	}
}