#include <stdio.h>
#include "defs.h"

void initRoomArray(RoomArrayType *arr){
	arr->size = 0;
}

void initRoom(int id, char *name, RoomType **room){
	RoomType *currentRoom = malloc(sizeof(RoomType));

	currentRoom->id = id;
	strcpy(currentRoom->name, name);
	
	GhostListType *currentGhostList = malloc(sizeof(GhostListType));
	currentRoom->ghosts = currentGhostList;

	*room = currentRoom;
}

void addRoom(RoomArrayType *arr, RoomType *r){
	arr->elements[arr->size] = r;
}

