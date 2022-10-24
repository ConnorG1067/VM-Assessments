#include <stdio.h>
#include <string.h>

#include "defs.h"

int main(void)
{
  int choice = 0;

  NotebookType* mainBook =  calloc(1, sizeof(NotebookType));

  initNotebook(mainBook, 2);
  loadEvidenceData(mainBook);
  while(1){
	printMenu(&choice);
	switch(choice){
    	case 1:
	  		//getting user input
	  		int id;
	  		char roomName[30];
	  		int deviceNumber;
			float value;
			int timestamp[3];

			//ID
			printf("Enter an ID: ");
			scanf("%d", &id);


			//Room Name
			printf("Enter a room name: "); 
			scanf(" ");
			fgets(roomName, sizeof(roomName), stdin);
			roomName[strcspn(roomName, "\n")] = '\0';

			//device number
			printf("Enter the device code [EMF: 1, THERMAL: 2, SOUND: 3]: ");
			scanf("%d", &deviceNumber);

			//Value
			printf("Enter the value: ");
			scanf("%f", &value);

			//Time stamp
			int timestampSize = 0;
			printf("Enter the timestamp (hours minutes seconds, space separated): ");
			while(timestampSize<3){
				scanf("%d", &timestamp[timestampSize++]);
			}

			char* device = calloc(8, sizeof(char));
			deviceSelector(device, deviceNumber);
			
			int timestampAsSeconds = timestampToSeconds(timestamp);

			EvidenceType tempEvidence;
			initEvidence(id, roomName, device, value, timestampAsSeconds, &tempEvidence);
			free(device);
			addEvidence(mainBook, &tempEvidence);
			break;
		case 2:
			int desiredId;
			printf("Enter the id you'd like to delete: ");
			scanf("%d", &desiredId);

			delEvidence(mainBook, desiredId);	
			break;
		case 3:
			printNotebook(mainBook);
			break;
		case 0:
  			cleanupNotebook(mainBook);
			return 0;


  	}
  }
  return(0);
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

