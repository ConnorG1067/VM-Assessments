#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define C_OK       0
#define C_NOK     -1

#define MAX_STR   32
#define MAX_CAP    2

typedef struct {	// base code
  int   id;
  char  room[MAX_STR];
  char  device[MAX_STR];
  float value;
  int   timestamp;
} EvidenceType;

typedef struct {
  EvidenceType *elements;
  int capacity;
  int size;
} NotebookType;


void printMenu(int*);
void loadEvidenceData(NotebookType*);

void initNotebook(NotebookType*, int);
void initEvidence(int, char*, char*, float, int, EvidenceType*);

void deviceSelector(char*, int);
int timestampToSeconds(int*);

void addEvidence(NotebookType*, EvidenceType*);
int  delEvidence(NotebookType*, int);
int  isFound(NotebookType*, int);
void copyEvidence(EvidenceType*, EvidenceType*);
void growNotebook(NotebookType*);
int elementShifter(NotebookType*, int);
void formatEvidence(EvidenceType*, char*);
void convertSecondsToTime(int, char*);
int shiftAndAdd(NotebookType*, EvidenceType*, int);
int checkTimestamp(NotebookType*, EvidenceType*, int);
void printNotebook(NotebookType*);
void cleanupNotebook(NotebookType*);
int getUserInput(int*, char*, char*, float*, int*);
