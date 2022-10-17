#include <stdio.h>
#include "defs.h"
#include <stdlib.h>
void copyEvidence(EvidenceType* newEv, EvidenceType* oldEv){
	initEvidence(oldEv->id, oldEv->room, oldEv->device, oldEv->value, oldEv->timestamp, &newEv);
}

void growNotebook(NotebookType* arr){
	arr->capacity*=2;
	arr = calloc(arr_capacity*2,sizeof(NotebookType));
	free(arr);
}
