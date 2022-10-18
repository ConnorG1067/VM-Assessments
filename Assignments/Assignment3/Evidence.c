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

//TODO Insert algorithm, done BUT we need to get timestamps working yo
void addEvidence(NotebookType* arr, EvidenceType* ev){
    if(arr->size == arr->capacity){
        growNotebook(arr);
    }

	//Insertion
    switch(arr->size){
        case 0:
			//if the array is empty just add the evidence
            arr->elements[arr->size] = *ev;
			break;
        default:
			//Otherwise check to see if the evidence belongs inbetween two existing evidences
            for(int i = 1; i<=arr->size; i++){
				//printf("%d %d %d\n",(int) arr->elements[i-1].room[0], (int) ev->room[0], (int) arr->elements[i].room[0]);
				//If it does exist between two particlar elements
				if((int) ev->room[0] <= arr->elements[i-1].room[0] && (int) ev->room[0] >= arr->elements[i].room[0]){	
					//Shift the elements to make space for the new element
					elementShifter(arr, i);
					//Set the ith element to the evidence
            		arr->elements[i] = *ev;
					//Increase the size
					arr->size++;
					//Return becuase we do not want to finish the rest of the code
					return;
				}
			}

			//If the element should not exist between elements, thus at the start of end, find the insert position
			int insertPos = ((int) ev->room[0] >= arr->elements[0].room[0]) ? 0 : arr->size;
			//Shift the elements in the array
			elementShifter(arr, insertPos);
			//Set the position of interest to the evidence
			arr->elements[insertPos] = *ev;
            break;
    }
	arr->size++;

}

int elementShifter(NotebookType* notebookArray, int shiftPos){
    for(int i = notebookArray->size-1; i>=shiftPos; i--){
        notebookArray->elements[i+1] = notebookArray->elements[i];
    }
}
