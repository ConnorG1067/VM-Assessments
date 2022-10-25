#include <stdio.h>
#include "defs.h"
#include <stdlib.h>
#include <math.h>

/***********************************************************************************************
 * Used to copy old evidence data to new evidence data
 * newEv is an in/out parameter which takes in the old data from the other parameter oldEv
 * oldEv is an in parameter which supplies the newEv with data
 * Return a void
************************************************************************************************/
void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv){
	initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, newEv);
}

/***********************************************************************************************
 * Used to grow the notebooks capacity
 * out parameter: arr is the notebook who's capcity will grow
 * Return a void
************************************************************************************************/
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

/***********************************************************************************************
 * Prints the notebook for the user
 * arr is an in paramter and is used to print the information the notebook holds
 * Return a void
************************************************************************************************/
void printNotebook(NotebookType* arr){
	printf("  ID |%16s Room |   Device |%11s Value  |  Timestamp\n", " ", " ");
	for(int i = 0; i<arr->size; i++){
	    char formattedStr[100] = "";
		formatEvidence(&arr->elements[i], formattedStr);
		printf("%s\n", formattedStr);
    
	}
}

/***********************************************************************************************
 * Adds evidence to the notebook first based on lexicographical order, then by timestamp
 * arr: in/out parameter, adds the given ev to itself
 * ev:  in parammeter, adds itself to the given arr
 * Return a void
************************************************************************************************/
void addEvidence(NotebookType* arr, EvidenceType* ev){
	//Grow the array size if the size is equal to the capacity
    if(arr->size == arr->capacity){
        growNotebook(arr);
    }
      
	//Loop through the array, starting at i = 1 so we can look at the previous element
	for(int i = 1; i<=arr->size; i++){
		//If the checkTimestamp function returns 0, that means we have added to the array and therefore, we can return
		if(checkTimestamp(arr, ev, i) == C_OK){
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

/***********************************************************************************************
 * Helper Function: If the room name already exists search for the timestamp within given rooms
 * arr: in/out parameter, used to determine information about the array and to modify the array
 * ev:  in parammeter, the given evidence to add
 * Return an int which determines the success of the operation
************************************************************************************************/
int checkTimestamp(NotebookType* arr, EvidenceType* ev, int i){
	if(strcmp(ev->room,arr->elements[i-1].room) == 0){
		//Loop while the current room is equal to the evidence room
		int indexCounter = i;
		while(strcmp(ev->room, arr->elements[indexCounter].room) == 0){
			//If at any point the room timestamp fits between shiftAndAdd then return
			if(ev->timestamp >= arr->elements[indexCounter-1].timestamp && ev->timestamp <= arr->elements[indexCounter].timestamp){
				shiftAndAdd(arr, ev, indexCounter);	
				return C_OK;
			}
			indexCounter++;
		}

		int insertPos = ev->timestamp <= arr->elements[i-1].timestamp ? i-1 : indexCounter;
		shiftAndAdd(arr, ev, insertPos);
		return C_OK;
	}
	return C_NOK;
}

/***********************************************************************************************************
 * Helper Function: calls the elementShifter to shift elements, then adds the ev to arr at position index
 * arr: out parameter, the array from which the elements are shifted and added
 * ev:  in parammeter, the given evidence to add 
 * index: in parameter, the index at which the evidence ev belongs
 * Return an int which determines the success of the operation
************************************************************************************************************/
int shiftAndAdd(NotebookType* arr, EvidenceType* ev, int index){
	elementShifter(arr, index);
	arr->elements[index] = *ev;
	arr->size++;
	return C_OK;
}

/*****************************************************************************************************
 * Helper Function: Formats the evidence, such that, printNotebook can print the content properly
 * evidence: in parameter, takes evidence information such that the formatting remains correct
 * stringBuilder: out parameter, the char array in which the formatted evidence is written to
 * Returns a void
******************************************************************************************************/
void formatEvidence(EvidenceType* evidence, char* stringBuilder){
	//Build a string	
	sprintf(stringBuilder, "%d | %20s | %8s |", evidence->id, evidence->room, evidence->device);
	if(strcmp(evidence->device, "EMF") == 0){
		char emfStr[MAX_STR] = "";
		sprintf(emfStr, "%.1f%s", evidence->value, (evidence->value>4) ? " (HIGH) |" : " |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %18s", emfStr);	
	}else if(strcmp(evidence->device, "THERMAL") == 0){
		char thermalStr[MAX_STR] = "";
		sprintf(thermalStr, "%.2f%s", evidence->value, (evidence->value<0.0) ? " (COLD) |" : " |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %18s", thermalStr);	
	}else{
		char soundStr[MAX_STR] = "";
		sprintf(soundStr, "%.1f%s", evidence->value, (evidence->value<35.0) ? " (WHISPER) |" : (evidence->value>70.0) ? " (SCREEM) |" : "  |");
		sprintf(stringBuilder + strlen(stringBuilder), "  %18s", soundStr);
	}
	char time[MAX_STR] = "";
	convertSecondsToTime(evidence->timestamp,time);
	sprintf(stringBuilder + strlen(stringBuilder), "%10s", time);
}

/***********************************************************************************************
 * Helper Function: converts given seconds to a HH:MM:SS format
 * seconds: in parameter, gives the provided seconds to calculate a time
 * time:  out parammeter, a char array to return the given time in a HH:MM:SS format
 * Returns a void
************************************************************************************************/
void convertSecondsToTime(int seconds, char* time){
	int exclusiveHours = seconds/3600;
	int exclusiveMinutes = (seconds % 3600)/60;
	int exclusiveSeconds = seconds % 60;
	sprintf(time, "%s%d:%s%d:%s%d", (exclusiveHours<10) ? "0" : ""  ,exclusiveHours, (exclusiveMinutes<10) ? "0" : "", exclusiveMinutes, (exclusiveSeconds<10) ? "0" : "", exclusiveSeconds);
}

/***********************************************************************************************
 * Helper Function: Shifts elements to the end of an array starting at shiftPos
 * notebookArray: in/out parameter, is the array in which elements are shifted
 * shiftPos: in parameter, is the starting index of the elements that are shifted
 * Returns an int to determine success
************************************************************************************************/
int elementShifter(NotebookType* notebookArray, int shiftPos){
    for(int i = notebookArray->size-1; i>=shiftPos; i--){
		copyEvidence(&notebookArray->elements[i+1], &notebookArray->elements[i]);
    }
}

/*************************************************************************************************************
 * Helper Function: searches through the array for an id, if found return the index otherwise return an error
 * arr: in parameter, used to check each element's id from the array
 * id:  in parammeter, a desired id to delete from the array
 * Returns the index of the position or an error code
*************************************************************************************************************/
int foundId(NotebookType* arr, int id){
	//Find the evidence with the given id, if not found return error flag (predefined constant)
	for(int i = 0; i<arr->size; i++){
		if(arr->elements[i].id == id){
			return i;
		}
	}
	return C_NOK;
}

/***********************************************************************************************
 * deletes evidence from the notebook
 * arr: in/out parameter, the array from which the element is being deleted
 * id: in parameter, used to determine the position of the id in the array
 * Returns an int to indicate success
************************************************************************************************/
int delEvidence(NotebookType* arr, int id){
	int idPosition = foundId(arr, id);
	if(idPosition > -1){
		for(int i = idPosition; i<arr->size; i++){
			copyEvidence(&arr->elements[i], &arr->elements[i+1]);
    	}
		arr->size--;
		return C_OK;
	}
	return C_NOK;
}

/***********************************************************************************************
 * free's all allocated memory from the notebook
 * arr: the array that has allocated memory
 * Returns a void
************************************************************************************************/
void cleanupNotebook(NotebookType* arr){
	free(arr->elements);
	free(arr);
}
