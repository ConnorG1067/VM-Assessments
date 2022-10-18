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
	printf("  ID |%16s Room |   Device |%8s Value  |  Timestamp\n", " ", " ");
	for(int i = 0; i<arr->size; i++){
	    char formattedStr[100] = "";
		formatEvidence(&arr->elements[i], formattedStr);
		printf("%s\n", formattedStr);
    
	}
}

//TODO Insert algorithm, done BUT we need to get timestamps working yo
//Abstract some stuff, pretty hectic
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

void formatEvidence(EvidenceType* evidence, char* stringBuilder){
	//Build a string	
	sprintf(stringBuilder, "%d | %20s | %8s |", evidence->id, evidence->room, evidence->device);
	if(strcmp(evidence->device, "EMF") == 0){
		char emfStr[50] = "";
		sprintf(emfStr, "%.1f%s", evidence->value, (evidence->value>4) ? " (HIGH) |" : " |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %15s", emfStr);	
	}else if(strcmp(evidence->device, "THERMAL") == 0){
		char thermalStr[50] = "";
		sprintf(thermalStr, "%.2f%s", evidence->value, (evidence->value<0.0) ? " (COLD) |" : " |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %15s", thermalStr);	
	}else{
		char soundStr[50] = "";
		sprintf(soundStr, "%.1f%s", evidence->value, (evidence->value<35.0) ? " (WHISPER) |" : (evidence->value>70.0) ? " (SCREEM) |" : "  |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %15s", soundStr);
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

}
