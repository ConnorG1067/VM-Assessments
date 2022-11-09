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
	initGhostList(currentGhostList);
	currentRoom->ghosts = currentGhostList;
	
	*room = currentRoom;
}

void addRoom(RoomArrayType *arr, RoomType *r){
	arr->elements[arr->size++] = r;
}

void cleanupRoomArray(RoomArrayType *arr){
	for(int i = 0; i<arr->size; i++){
		cleanupGhostData(arr->elements[i]->ghosts);
		cleanupGhostList(arr->elements[i]->ghosts);
		free(arr->elements[i]);

	}
}

void printRooms(RoomArrayType *arr){
	for(int i = 0; i<arr->size; i++){
		printf("ROOM: %s\n ", arr->elements[i]->name);
		printGhosts(arr->elements[i]->ghosts, 0);
	}

}

