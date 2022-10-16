#include <stdio.h>
#include "defs.h"
#include <stdlib.h>
void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv){
	initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, newEv);
}

void growNotebook(NotebookType* arr){
	NotebookType* newNotebook;
	initNotebook(newNotebook, sizeof(arr)*2);
	for(int i = 0; i<sizeof(arr); i++){
		copyEvidence(&newNotebook->elements[i], &arr->elements[i]);
		
	}
	free(arr);
}
