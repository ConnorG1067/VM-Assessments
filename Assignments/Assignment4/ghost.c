#include <stdio.h>
#include "defs.h"

void initGhostList(GhostListType *list){
	list->head = NULL;
	list->tail = NULL;
}

void initGhost(int id, GhostEnumType gt, RoomType *r, float like, GhostType **ghost){
	//Allocate for GhostType	
	GhostType *ghostPointer = malloc(sizeof(GhostType));
	//Set Fields
	ghostPointer->id = id;
	ghostPointer->ghostType = gt;
	ghostPointer->room = r;
	ghostPointer->likelihood = like;

	//Set the pointer to the new ghost pointer
	*ghost = ghostPointer;
	
}

void addGhost(GhostListType *list, GhostType *ghost){
	//Making a new node
	NodeType *currentNode = malloc(sizeof(NodeType));

	//Setting the values of new node
	currentNode->data = ghost;
	currentNode->next = NULL;

	
	//Setting the end of the list to the new node
	if(list->head == NULL){
		list->head = currentNode;
		list->tail = currentNode;
	}else{
		list->tail->next = currentNode;
		list->tail = list->tail->next;
	}
	
		
}

void addGhostByLikelihood(GhostListType *list, GhostType *ghost){
	NodeType *ghostNode = malloc(sizeof(NodeType));
	ghostNode->data = ghost;
	ghostNode->next = NULL;
	
	//LIST IS EMPTY
	if(list->head == NULL){
		list->head = ghostNode;
		list->tail = ghostNode;
		return;
	}
    //IF WE REPLACE FRONT	
	if(ghost->likelihood >= list->head->data->likelihood){
		ghostNode->next = list->head;
		list->head = ghostNode;
		return;
	}
	
	//Traverse through the linked list and compare the likelihood of the current ghost to the other ghosts
	NodeType *traverseNode = list->head;
	while(traverseNode->next != NULL){
		if(ghost->likelihood >= traverseNode->next->data->likelihood){
			NodeType *tempNode = traverseNode->next;
			traverseNode->next = ghostNode;
			ghostNode->next = tempNode;
			return;
		}
		traverseNode = traverseNode->next;
	}
	
	list->tail->next = ghostNode;
	list->tail = ghostNode;
	ghostNode->next = NULL;	
}

void cleanupGhostData(GhostListType *list){	
	NodeType *tempNode = list->head;
	while(tempNode != NULL){
		free(tempNode->data);
		tempNode = tempNode->next;
	}
}


void cleanupGhostList(GhostListType *list){
	NodeType *tempNode;
	while(list->head != NULL){
		tempNode = list->head;
		list->head = list->head->next;
		free(tempNode);
	}
}

void printGhost(GhostType *ghost){
	printf("|%-12d %-14s %-19s %-7.2f|\n", ghost->id,typeToString(ghost->ghostType), (ghost->room != NULL) ? ghost->room->name : "N/A", ghost->likelihood);
}

void printGhosts(GhostListType *list, int ends){	
	NodeType *loopNode = list->head;
	while(loopNode != NULL){
		printGhost(loopNode->data);
		loopNode = loopNode->next;
	}

	if(ends == C_TRUE){
		printf("\nHead and Tail\n");
		printGhost(list->head->data);
		printGhost(list->tail->data);

	}

}

void printByLikelihood(GhostListType *origList, int ends){
	GhostListType tempList;
	GhostListType *tempListPtr = &tempList;
	initGhostList(tempListPtr);

	
	NodeType *tempOrigHead = origList->head;
	while(tempOrigHead != NULL){
		addGhostByLikelihood(tempListPtr, tempOrigHead->data);
		tempOrigHead = tempOrigHead->next;
	}

	
	NodeType *tempTraverse = tempListPtr->head;
	while(tempTraverse != NULL){
		printGhost(tempTraverse->data);
		tempTraverse = tempTraverse->next;
		
	}

	cleanupGhostList(tempListPtr);
}
