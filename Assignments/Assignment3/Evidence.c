#include <stdio.h>
#include "defs.h"
#include <stdlib.h>


void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv){
	initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, newEv);
}

void growNotebook(NotebookType* arr){ 
    NotebookType* newNotebook = calloc(1, sizeof(NotebookType));
	initNotebook(newNotebook, arr->capacity*2);
	for(int i = 0; i<arr->size; i++){
		copyEvidence(&newNotebook->elements[i], &arr->elements[i]);
	}
   free(arr->elements);
   arr->elements = newNotebook->elements;
   arr->capacity*=2;
}
//TODO Valgrind says we are losing bytes, fix this
void printNotebook(NotebookType* arr){
	printf("  ID |%16s Room |   Device |%9s Value  |  Timestamp\n", " ", " ");
	for(int i = 0; i<arr->size; i++){
	   printf("%d | %20s | %8s |  %13f  |  %9d\n", arr->elements[i].id, arr->elements[i].room, arr->elements[i].device, arr->elements[i].value, arr->elements[i].timestamp);
    
	}
}

//TODO Insert algorithm
void addEvidence(NotebookType* arr, EvidenceType* ev){
    if(arr->size == arr->capacity){
        growNotebook(arr);
    }
    switch(arr->size){
        case 0:
            arr->elements[arr->size++] = *ev;
            break;
        default:

            for(int i = 0; i<arr->size; i++){
                printf("%c %c ",ev->room[0], arr->elements[i].room[0]);
                printf("%d ", ev->room[0]>=arr->elements[i].room[0]);

                printf("%d\n", ev->room[0]<=arr->elements[i].room[0]);
                if((int) ev->room[0] >= (int) arr->elements[i].room[0] && (int) ev->room[0] <=arr->elements[i+1].room[0]){
                    elementShifter(arr, i+1);
                    arr->elements[i+1] = *ev;
                }
             }
            break;
    }
}

int elementShifter(NotebookType* notebookArray, int shiftPos){
    for(int i = notebookArray->size-1; i>shiftPos; i--){
        notebookArray->elements[i+1] = notebookArray->elements[i];
        notebookArray->size++;
    }
}
