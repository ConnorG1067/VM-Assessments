#include <stdio.h>
#include "defs.h"


/*********************************************************************************************
 * Initalizes a ghost list
 * out: list, sets the head & tail to NULL
 ********************************************************************************************/
void initGhostList(GhostListType *list){
	list->head = NULL;
	list->tail = NULL;
}

/*********************************************************************************************
 * Initalizes a ghost type
 * in: id, is the id assoicated with the ghost
 * in: gt, is the ghostTypeEnum assoicated with the ghost
 * in: r, is the room that the current ghost is in
 * out: ghost, is the ghost we want to initalize
 * out: Sets the head & tail to NULL
 ********************************************************************************************/
void initGhost(int id, GhostEnumType gt, RoomType *r, float like, GhostType **ghost){
	//Allocate memory for the ghost	
	GhostType *ghostPointer = malloc(sizeof(GhostType));

	//Set Fields
	ghostPointer->id = id;
	ghostPointer->ghostType = gt;
	ghostPointer->room = r;
	ghostPointer->likelihood = like;

	//Set the pointer to the new ghost pointer
	*ghost = ghostPointer;
	
}


 /*********************************************************************************************
 * Appends the ghost to the end of the given list
 * in: ghost, is the ghost to add
 * in/out: list, is the list that we want to add the element to 
 ********************************************************************************************/
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

/*********************************************************************************************
 * Adds a ghost by its likelihood in decending order
 * in: ghost, is the ghost to add
 * in/out: list, is the list that we want to add the element to 
 ********************************************************************************************/
void addGhostByLikelihood(GhostListType *list, GhostType *ghost){
	//Creating the ghost
	NodeType *ghostNode = malloc(sizeof(NodeType));
	ghostNode->data = ghost;
	ghostNode->next = NULL;
	
	//Head is null implies list is empty
	if(list->head == NULL){
		list->head = ghostNode;
		list->tail = ghostNode;
	//If the ghost belongs at the head
	}else if(ghost->likelihood >= list->head->data->likelihood){
		ghostNode->next = list->head;
		list->head = ghostNode;
		return;
	}else{
		//Traverse through the linked list and compare the likelihood of the current ghost to the other ghosts
		NodeType *traverseNode = list->head;
		while(traverseNode->next != NULL){
			//If the ghosts likelihood is greater than the current ghost then insert the ghost
			if(ghost->likelihood >= traverseNode->next->data->likelihood){
				NodeType *tempNode = traverseNode->next;
				traverseNode->next = ghostNode;
				ghostNode->next = tempNode;
				return;
			}
			traverseNode = traverseNode->next;
		}
		//If the ghost is never inserted, add it to the tail
		list->tail->next = ghostNode;
		list->tail = ghostNode;
		ghostNode->next = NULL;	
	}
}

/*********************************************************************************************
 * Prints a the provided ghost 
 * in: ghost, used to print the structures data
 *********************************************************************************************/
void printGhost(GhostType *ghost){
	//Print the ghost, if room is NULL then it is unknown
	printf("|%-12d %-14s %-19s %-7.2f|\n", ghost->id,typeToString(ghost->ghostType), (ghost->room != NULL) ? ghost->room->name : "Unknown", ghost->likelihood);
}

/*********************************************************************************************
 * Takes a GhostEnumType and return a string of the cooresponding
 * in: type, the type which provides an integer to the switch
 *********************************************************************************************/
char* typeToString(GhostEnumType type){
	switch(type){
		case POLTERGEIST:
			return "Poltergeist";
		case WRAITH:
			return "Wraith";
		case PHANTOM:
			return "Phantom";
		case BULLIES:
			return "Bullies";
		case OTHER:
			return "OTHER";
	}
}

/*********************************************************************************************
 * Prints all ghosts of a given ghost list using the printGhost function 
 * in: list, the list of nodes we intend to print
 * in: ends, determine whether the head and tail will be printed at the end
 *********************************************************************************************/
void printGhosts(GhostListType *list, int ends){
	//Traverse through the linked list and print the current ghost each iteration
	NodeType *loopNode = list->head;
	while(loopNode != NULL){
		printGhost(loopNode->data);
		loopNode = loopNode->next;
	}

	//If the ends arg is true, print the head and tail
	if(ends == C_TRUE){
		printf("\nHead and Tail\n");
		printGhost(list->head->data);
		printGhost(list->tail->data);
	}
}

/*********************************************************************************************
 * Prints all ghosts by their likelihood in decending order
 * in: origList, the list of nodes we intend to print
 * in: ends, determine whether the head and tail will be printed at the end
 *********************************************************************************************/
void printByLikelihood(GhostListType *origList, int ends){
	//Make a new list
	GhostListType tempList;
	GhostListType *tempListPtr = &tempList;
	initGhostList(tempListPtr);

	//Traverse through the origList and add each iteration to the new tempListPtr
	NodeType *tempOrigHead = origList->head;
	while(tempOrigHead != NULL){
		addGhostByLikelihood(tempListPtr, tempOrigHead->data);
		tempOrigHead = tempOrigHead->next;
	}

	//Print the ghosts of the new tempListPtr
	printGhosts(tempListPtr, ends);
	cleanupGhostList(tempListPtr);
}

/*********************************************************************************************
 * Frees all the data stored within the nodes of the linked list 
 * in: list, used to free all of the data within its node
 *********************************************************************************************/
void cleanupGhostData(GhostListType *list){	
	NodeType *tempNode = list->head;
	while(tempNode != NULL){
		free(tempNode->data);
		tempNode = tempNode->next;
	}
}

/*********************************************************************************************
 * Frees all the nodes of the linked list 
 * in: list, used to free all of its node
 *********************************************************************************************/
void cleanupGhostList(GhostListType *list){
	NodeType *tempNode;
	while(list->head != NULL){
		tempNode = list->head;
		list->head = list->head->next;
		free(tempNode);
	}
}
