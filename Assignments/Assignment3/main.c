#include <stdio.h>
#include <string.h>

#include "defs.h"

int main(void)
{
  int choice = 0;
  printMenu(&choice);

  NotebookType* mainBook = (NotebookType *) calloc(1, sizeof(NotebookType));

  initNotebook(mainBook, 2);
  loadEvidenceData(mainBook);
  switch(choice){
    case 1:
	  break;
	case 2:
	  break;
	case 3:
      printNotebook(mainBook);
	  break;
  }
  free(mainBook);
  return(0);
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

