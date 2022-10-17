#include <stdio.h>
#include "defs.h"
#include <stdlib.h>


void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv){
	initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, newEv);
}

void growNotebook(NotebookType* arr){ 
    arr->capacity *= 2;
    NotebookType* newNotebook = (NotebookType *) calloc(1, sizeof(NotebookType));
	initNotebook(newNotebook, arr->capacity);
	for(int i = 0; i<arr->size; i++){
		copyEvidence(newNotebook->elements, arr->elements);
	}

    /*
    printf("YOi\n");

	arr->capacity*=2;

    printf("IN IF CAPACITY: %d\n", arr->capacity);
	arr = calloc(arr->capacity,sizeof(NotebookType));
    
    printf("3nd YO!\n");
    */

}

void printNotebook(NotebookType* arr){
    printf("%d\n", arr->size);
	for(int i = 0; i<arr->size; i++){
		printf("%s %d\n", arr->elements[i].room, i);
	}
}

void addEvidence(NotebookType* arr, EvidenceType* ev){
    if(arr->size == arr->capacity){
        growNotebook(arr);

    }
    arr->elements[arr->size++] = *ev;
   
    
}
