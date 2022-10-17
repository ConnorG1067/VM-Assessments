#include <stdio.h>
#include "defs.h"
#include <stdlib.h>
void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv){
	initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, newEv);
}

void growNotebook(NotebookType* arr){
	NotebookType* newNotebook;
	initNotebook(newNotebook, arr->capacity*2);
	for(int i = 0; i<arr->size; i++){
		copyEvidence(arr->elements, newNotebook->elements);
	}


	/*
	arr->capacity*=2;
	arr = calloc(arr_capacity*2,sizeof(NotebookType));
	free(arr);
	*/
}

void printNotebook(NotebookType* arr){
	for(int i = 0; i<arr->size; i++){
		printf("%d\n", arr->elements->id);

	}
}
