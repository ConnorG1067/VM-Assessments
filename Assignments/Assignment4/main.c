#include "defs.h"

int main()
{
  int selection = 0;
  printMenu(&selection);
  BuildingType building;
  initBuilding(&building);
  loadBuildingData(&building);
  switch(selection){
    case 0:
	  break;
	case 1:
	  printRooms(&building.rooms);
	  break;
	case 2:
	  printGhosts(&building.ghosts, 0);
	  break;
	case 3:
	  printf("3");
	  break;
  }
  cleanupBuilding(&building);
  return(0);
}

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

