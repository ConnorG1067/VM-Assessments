#include "defs.h"

int main(){
	//Making, initalizing and loading a building type
  	BuildingType building;
  	initBuilding(&building);
  	loadBuildingData(&building);
 	 while(1){
		//print the menu
		int selection = 0;
		printMenu(&selection);
  		switch(selection){
    		case 0:
  				cleanupBuilding(&building);
				return 0;
			case 1:
	  			printRooms(&building.rooms);
	  			break;
			case 2:
				printf("\n---------------------------------------------------------\n");
	  			printGhosts(&building.ghosts, C_TRUE);
				printf("---------------------------------------------------------\n");
	  			break;
			case 3:
				printf("\n---------------------------------------------------------\n");
	  			printByLikelihood(&building.ghosts, 0);
				printf("---------------------------------------------------------\n");
	  			break;
  		}
 	}
	return 0;
}

/*********************************************************************************************
 * print the menu for th user
 * out: choice, the selection for the user
 *********************************************************************************************/
void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print rooms\n");
  printf("  (2) Print ghosts\n");
  printf("  (3) Print ghosts by likelihood\n");
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

