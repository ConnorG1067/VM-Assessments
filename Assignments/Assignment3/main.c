#include <stdio.h>
#include <string.h>

#include "defs.h"

int main(void)
{
  int choice = 0;

  NotebookType* mainBook =  calloc(1, sizeof(NotebookType));

  initNotebook(mainBook, MAX_CAP);
  loadEvidenceData(mainBook);
  while(1){
	printMenu(&choice);
	switch(choice){
    	case 1:
	  		//getting user input
	  		int id;
	  		char* roomName = calloc(MAX_STR, sizeof(char));
			float value;
			char* deviceType = calloc(8, sizeof(char));
			int timestampAsSeconds;

			//Get the user input using pass by reference
			getUserInput(&id, roomName, deviceType, &value, &timestampAsSeconds);

			//Init evidence
			EvidenceType tempEvidence;
			initEvidence(id, roomName, deviceType, value, timestampAsSeconds, &tempEvidence);
			//Free the device string
			free(deviceType);
			free(roomName);
			//Add the evidence
			addEvidence(mainBook, &tempEvidence);
			break;
		case 2:
			int desiredId;
			printf("Enter the ID you'd like to delete: ");
			scanf("%d", &desiredId);
			
			//Attempt to delete Id, & print a user friendly message
			if(delEvidence(mainBook, desiredId) == 0){
				printf("\nID %d Deleted\n", desiredId);
				printNotebook(mainBook);
			}else{
				printf("\nCould not find ID: %d\n", desiredId);
			}
			break;
		case 3:
			printNotebook(mainBook);
			break;
		case 0:
  			cleanupNotebook(mainBook);
			return C_OK;


  	}
  }
  return C_OK;
}


/***************************************************************************************************************
 * Helper Function: Gets user input and error checks specific values
 * timestampArray: in parameter, consisting of 3 integer values which represent the hours, minutes and seconds
 * Returns an integer of the seconds
****************************************************************************************************************/
int getUserInput(int* id, char* roomName, char* deviceType, float* value, int* timestampAsSeconds){
	//Defualt helper variables
	int deviceNumber;
	int timestamp[3];
	char tempRoomName[MAX_STR];
	
	//Getting the ID
	printf("Enter an ID: ");
	scanf("%d", id);

	while(*id >= 100000 || *id < 0){
		printf("Enter a valid ID: ");
		scanf("%d", id);
	}
	

	//Getting the room name 	
	printf("Enter a room name: "); 
	scanf(" ");
	fgets(tempRoomName, sizeof(tempRoomName), stdin);
	tempRoomName[strcspn(tempRoomName, "\n")] = '\0';
	strcpy(roomName, tempRoomName);


	//device number
	printf("Enter the device code [EMF: 1, THERMAL: 2, SOUND: 3]: ");
	scanf("%d", &deviceNumber);
	while(deviceNumber > 3 || deviceNumber < 0){
		printf("Enter a valid device code [EMF: 1, THERMAL: 2, SOUND: 3]: ");
		scanf("%d", &deviceNumber);

	}
	//Copys a string based on the device number
	deviceSelector(deviceType, deviceNumber);

	//Getting the value
	printf("Enter the value: ");
	scanf("%f", value);

	//getting the time stamp
	int timestampSize = 0;
	printf("Enter the timestamp (hours minutes seconds, space separated): ");
	while(timestampSize<3){
		scanf("%d", &timestamp[timestampSize++]);
	}

	*timestampAsSeconds = timestampToSeconds(timestamp);

	return 0;
}

/***************************************************************************************************************
 * Helper Function: converts the given timestamp to seconds
 * timestampArray: in parameter, consisting of 3 integer values which represent the hours, minutes and seconds
 * Returns an integer of the seconds
****************************************************************************************************************/
int timestampToSeconds(int* timestampArray){
	return (timestampArray[0]*3600) + (timestampArray[1]*60) + (timestampArray[2]);
}


/***************************************************************************************************************
 * Helper Function: copys the value associated with the choice to the char array
 * deviceString: out parameter, consists of the characters of the type of device
 * choice: in parameter which dictates the device based on an integer value
 * Returns a void
****************************************************************************************************************/
void deviceSelector(char* deviceString, int choice){
	switch(choice){
		case 1:
			strcpy(deviceString, "EMF");
			break;
		case 2:
			strcpy(deviceString, "THERMAL");
			break;
		case 3:
			strcpy(deviceString, "SOUND");
			break;
	}
}
/***************************************************************************************************************
 * Prints a menu for the user
 * choice: in/out parameter, stores the choice the user picks
 * Returns a void
****************************************************************************************************************/
void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Add evidence\n");
  printf("  (2) Delete evidence\n");
  printf("  (3) Print evidence\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}

