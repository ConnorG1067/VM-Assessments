#include <stdio.h>
#include "defs.h"

void initGhostList(GhostListType *list){
	list->head = NULL;
	list->tail = NULL;
}

void initGhost(int id, GhostEnumType gt, RoomType *r, float like, GhostType **ghost){
	//Allocate for GhostType
	GhostType *ghostPointer = calloc(1, sizeof(GhostType));

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
	struct Node *currentNode = malloc(sizeof(NodeType));

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
	
	/*
	printf("-------------------------------\n");
	printGhosts(list, 0);
	
	printf("-------------------------------\n");
	*/
		
}

//COULD BE DOG SHIT I DUNNO
void addGhostByLikelihood(GhostListType *list, GhostType *ghost){
	//Traverse through the linked list and compare the likelihood of the current ghost to the other ghosts
	NodeType *traverseNode = list->head;

	//Make a node for the currentGhost
	NodeType *ghostNode = malloc(sizeof(NodeType));
	ghostNode->data = ghost;

	
	if(ghost->likelihood >= list->head->data->likelihood){
		ghostNode->next = list->head;
		list->head = ghostNode;
		return;
	}
	
	while(traverseNode != NULL){
		if(ghost->likelihood >= traverseNode->next->data->likelihood){
			NodeType *tempNode = traverseNode->next;
			traverseNode->next = ghostNode;
			ghostNode->next = tempNode;
			return;
		}
		traverseNode = traverseNode->next;
	}

	list->tail->next = ghostNode;
	ghostNode->next = NULL;
}

//Free Stuff
void cleanupGhostData(GhostListType *list){	
	NodeType *tempNode = list->head;
	while(tempNode != NULL){
		free(tempNode->data);
		tempNode = tempNode->next;
	}
}


//SHOULD BREAK :/
void cleanupGhostList(GhostListType *list){
	NodeType *tempNode = list->head;
	while(tempNode != NULL){
		free(tempNode);
		tempNode = tempNode->next;
	}
}

void printGhost(GhostType *ghost){
	printf("ID: %d\tName: %d\tRoom: %s\tLikelihood: %f\n", ghost->id, ghost->ghostType, (ghost->room != NULL) ? ghost->room->name : "N/A", ghost->likelihood);
}

void printGhosts(GhostListType *list, int ends){
	NodeType *loopNode = list->head;
	while(loopNode != NULL){
		printGhost(loopNode->data);
		loopNode = loopNode->next;
	}
}
