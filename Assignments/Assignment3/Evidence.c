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
		copyEvidence(newNotebook->elements, arr->elements);
	}
   //TODO FREE
   free(arr->elements);
   arr = newNotebook;
   arr->capacity*=2;
}

void printNotebook(NotebookType* arr){
	printf("  ID |%16s Room |   Device |%9s Value  |  Timestamp\n", " ", " ");
	for(int i = 0; i<arr->size; i++){
	   printf("%d | %20s | %8s |  %13f  |  %9d\n", arr->elements[i].id, arr->elements[i].room, arr->elements[i].device, arr->elements[i].value, arr->elements[i].timestamp);
    
	}
}

void addEvidence(NotebookType* arr, EvidenceType* ev){
    if(arr->size == arr->capacity){
        growNotebook(arr);
    }
    arr->elements[arr->size++] = *ev; 
}
