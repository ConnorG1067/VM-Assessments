#include <stdio.h>
#include "defs.h"
#include <stdlib.h>
#include <math.h>
//TODO
//1. SORT BY TIMESTAMP IF THE SAME NAME!
//2. BREAK UP INSERT ALGORITHM
//3. CLEAN UP FUNCTION
//4. ADD/DEL functionality


void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv){
	initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, newEv);
}

void growNotebook(NotebookType* arr){ 
    NotebookType* newNotebook = (NotebookType*) calloc(1, sizeof(NotebookType));
	initNotebook(newNotebook, arr->capacity*2);
	for(int i = 0; i<arr->size; i++){
		copyEvidence(&newNotebook->elements[i], &arr->elements[i]);
	}
    free(arr->elements);
    arr->elements = newNotebook->elements;
    free(newNotebook);
    arr->capacity*=2;
}

void printNotebook(NotebookType* arr){
	printf("  ID |%16s Room |   Device |%8s Value  |  Timestamp\n", " ", " ");
	for(int i = 0; i<arr->size; i++){
	    char formattedStr[100] = "";
		formatEvidence(&arr->elements[i], formattedStr);
		printf("%s\n", formattedStr);
    
	}
}


void addEvidence(NotebookType* arr, EvidenceType* ev){
	//Grow the array size if the size is equal to the capacity
    if(arr->size == arr->capacity){
        growNotebook(arr);
    }
      
	//Loop through the array, starting at i = 1 so we can look at the previous element
	for(int i = 1; i<=arr->size; i++){
		//If the checkTimestamp function returns 0, that means we have added to the array and therefore, we can return
		if(checkTimestamp(arr, ev, i) == 0){
			return;
		}

		//Check to see if the room is less than the current and greater than the adjancent current but not equal
		//In other words, if we find a unique room name and it can be put between two distinct room names, do so.
		if((strcmp(ev->room,arr->elements[i-1].room)<0) && (strcmp(ev->room,  arr->elements[i].room)>0)){
			shiftAndAdd(arr, ev, i);
			return;
		}		
	}

	//If the room name does not fit in the middle, then it must go at the start or the end
	int insertPos = (strcmp(ev->room, arr->elements[0].room) > 0) ? 0 : arr->size;
	shiftAndAdd(arr, ev, insertPos);
	
}

int checkTimestamp(NotebookType* arr, EvidenceType* ev, int i){
	if(strcmp(ev->room,arr->elements[i-1].room) == 0){
		//Add at the beginning, hence i-1
		if(ev->timestamp <= arr->elements[i-1].timestamp){
			shiftAndAdd(arr, ev, i-1);	
			return 0;
		}

		//Loop while the current room is equal to the evidence room
		int indexCounter = i;
		while(strcmp(ev->room, arr->elements[indexCounter].room) == 0){
			//If at any point the room timestamp fits between shiftAndAdd then return
			if(ev->timestamp >= arr->elements[indexCounter-1].timestamp && ev->timestamp <= arr->elements[indexCounter].timestamp){
				shiftAndAdd(arr, ev, indexCounter);	
				return 0;
			}
			indexCounter++;
		}
		//If we are equal with the room but it does not go in the start or middle, it must go at the end
		shiftAndAdd(arr, ev, indexCounter);	
		return 0;
	}
	return -1;
}

int shiftAndAdd(NotebookType* arr, EvidenceType* ev, int index){
	elementShifter(arr, index);
	arr->elements[index] = *ev;
	arr->size++;
	return 0;
}

void formatEvidence(EvidenceType* evidence, char* stringBuilder){
	//Build a string	
	sprintf(stringBuilder, "%d | %20s | %8s |", evidence->id, evidence->room, evidence->device);
	if(strcmp(evidence->device, "EMF") == 0){
		char emfStr[50] = "";
		sprintf(emfStr, "%.1f%s", evidence->value, (evidence->value>4) ? " (HIGH) |" : " |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %18s", emfStr);	
	}else if(strcmp(evidence->device, "THERMAL") == 0){
		char thermalStr[50] = "";
		sprintf(thermalStr, "%.2f%s", evidence->value, (evidence->value<0.0) ? " (COLD) |" : " |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %18s", thermalStr);	
	}else{
		char soundStr[50] = "";
		sprintf(soundStr, "%.1f%s", evidence->value, (evidence->value<35.0) ? " (WHISPER) |" : (evidence->value>70.0) ? " (SCREEM) |" : "  |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %18s", soundStr);
	}
	char time[10] = "";
	convertSecondsToTime(evidence->timestamp,time);
	sprintf(stringBuilder + strlen(stringBuilder), "%10s", time);
}

void convertSecondsToTime(int seconds, char* time){
	int exclusiveHours = seconds/3600;
	int exclusiveMinutes = (seconds % 3600)/60;
	int exclusiveSeconds = seconds % 60;
	sprintf(time, "%s%d:%s%d:%s%d", (exclusiveHours<10) ? "0" : ""  ,exclusiveHours, (exclusiveMinutes<10) ? "0" : "", exclusiveMinutes, (exclusiveSeconds<10) ? "0" : "", exclusiveSeconds);
}


int elementShifter(NotebookType* notebookArray, int shiftPos){
    for(int i = notebookArray->size-1; i>=shiftPos; i--){
        notebookArray->elements[i+1] = notebookArray->elements[i];
    }
}

void cleanupNotebook(NotebookType* arr){
	free(arr->elements);

}
