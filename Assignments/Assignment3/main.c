#include <stdio.h>
#include <string.h>

#include "defs.h"

int main(void)
{
  int choice = 0;

  NotebookType* mainBook = (NotebookType *) calloc(1, sizeof(NotebookType));

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

			//device number
			printf("Enter the device code [EMF: 1, THERMAL: 2, SOUND: 3]: ");
			scanf("%d", &deviceNumber);

			//Value
			printf("Enter the value: ");
			scanf("%f", &value);

			//Value
			int timestampSize = 0;

			printf("Enter the timestamp (hours minutes seconds, space separated): ");
			while(timestampSize<3){
					scanf("%d", &timestamp[timestampSize++]);

			}

			char* device = deviceSelector(deviceNumber);
			int timestampAsSeconds = timestampToSeconds(timestamp);

            printf("%d\n", id);
            printf("%s\n", roomName);
            printf("%s\n", device);
            printf("%f\n", value);

            //Pretty horrible, ideally no loop
            for(int i = 0; i<30; i++){
                if(roomName[i] == '\n'){
                    roomName[i] = '\0';
                }
            }

			EvidenceType tempEvidence;
			initEvidence(id, roomName, device, value, timestampAsSeconds, &tempEvidence);
			addEvidence(mainBook, &tempEvidence);

			break;
		case 2:


			break;
		case 3:
			printNotebook(mainBook);
			break;
		case 0:
			return 0;


  	}
  }
  free(mainBook);
  return(0);
}

//Convert timestamp to seconds
int timestampToSeconds(int* timestampArray){
	return (timestampArray[0]*3600) + (timestampArray[1]*60) + (timestampArray[2]);
}


//Converts choice to device name
char* deviceSelector(int choice){
	char* deviceString = calloc(7, sizeof(char));
	switch(choice){
		case 1:
			deviceString = "EMF";
			break;
		case 2:
			deviceString = "THERMAL";
			break;
		case 3:
			deviceString = "SOUND";
			break;
	}
	return deviceString;
}

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

