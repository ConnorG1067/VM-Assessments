#include <stdio.h>
#include "defs.h"

/*********************************************************************************************
 * Initalizes the room array
 * out: arr, set the array size to 0
 *********************************************************************************************/
void initRoomArray(RoomArrayType *arr){
	arr->size = 0;
}

/*********************************************************************************************
 * Initalizes the room given as a parameter
 * in: id, assign the id to the room
 * in: name, assign the name to the room
 * out: room, the room the be initalized
 **********************************************************************************************/
void initRoom(int id, char *name, RoomType **room){
	RoomType *currentRoom = malloc(sizeof(RoomType));

	currentRoom->id = id;
	strcpy(currentRoom->name, name);
	
	GhostListType *currentGhostList = malloc(sizeof(GhostListType));
	initGhostList(currentGhostList);
	currentRoom->ghosts = currentGhostList;
   	
	*room = currentRoom;
}

/*********************************************************************************************
 * Adds a room to the arr
 * out: arr, is the array of rooms that r is being added to
 * in:  r, is the room we wish to add to the array
 *********************************************************************************************/
void addRoom(RoomArrayType *arr, RoomType *r){
	arr->elements[arr->size++] = r;
}

/*********************************************************************************************
 * Clean up the room array
 * in: arr, is the array of rooms that are to be cleaned 
 *********************************************************************************************/
void cleanupRoomArray(RoomArrayType *arr){
	//Loop throught the array and cleanup allocated memory
	for(int i = 0; i<arr->size; i++){
		cleanupGhostList(arr->elements[i]->ghosts);
		free(arr->elements[i]->ghosts);
		free(arr->elements[i]);
	}
}
/*********************************************************************************************
 * Prints all of the rooms with its assoicated ghosts
 * in: arr, is the array of rooms we wish to print 
 *********************************************************************************************/
void printRooms(RoomArrayType *arr){
	printf("\n");
	//Loop throught the array and print the data
	for(int i = 0; i<arr->size; i++){
		printf("---------------------------------------------------------\n");
		printf("|%-4d %-50s|\n", arr->elements[i]->id, arr->elements[i]->name);
		printGhosts(arr->elements[i]->ghosts, C_FALSE);
		printf("---------------------------------------------------------\n\n");
	}
}

