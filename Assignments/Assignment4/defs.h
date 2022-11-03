#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define C_TRUE     1
#define C_FALSE    0
 
#define MAX_ARR  128
#define MAX_STR   32
 
#define NEXT_ROOM_ID    9001
#define NEXT_GHOST_ID  810310
 
typedef enum { POLTERGEIST, WRAITH, PHANTOM, BULLIES, OTHER } GhostEnumType;
 
typedef struct {
  int id;
  char name[MAX_STR];
  struct GhostList *ghosts;
} RoomType;
 
typedef struct {
  int id;
  GhostEnumType ghostType;
  RoomType *room;
  float likelihood;
} GhostType;
 

/*** Define the RoomArrayType here ***/
 
/*** Define the NodeType here ***/
 
/*** Complete the GhostListType here ***/
typedef struct GhostList {
 
} GhostListType;

/*** Complete the BuildingType here ***/
typedef struct Building {
 
} BuildingType;
 
 
void printMenu(int*);
 
 
 

