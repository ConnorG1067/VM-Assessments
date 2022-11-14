#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "t07defs.h"

/* Implement the following functions */
int insertStudentAlpha(StudentList *, StudentType *);
int deleteStudent(StudentList *, char *, char *);
int cleanupList(StudentList *);

int main(void) {
  int i, rc;
  
  StudentType *matilda, *joe, *timmy;

  initStudent("Matilda", "Mallister", 22, "123444555",9.0, &matilda);
  initStudent("Joe", "The Plumber", 24, "567888999",8.7, &joe);
  initStudent("Timmy", "Tortoise", 99, "345667788",11.5, &timmy); 
 
  StudentList *comp2401 = malloc(sizeof(StudentList));

  comp2401->head = NULL;

  insertStudentAlpha(comp2401, matilda);
  insertStudentAlpha(comp2401, joe);
  insertStudentAlpha(comp2401, timmy);
  printList(comp2401);

  rc = deleteStudent(comp2401, "Tommy", "Tortoise");
  printf("%d\n", rc);
  rc = deleteStudent(comp2401, "Joe", "The Plumber"); 
  printf("%d\n", rc);
  printList(comp2401);
  deleteStudent(comp2401, "Matilda", "Mallister");
  printList(comp2401);
  

  cleanupList(comp2401);

  return 0;
}

int insertStudentAlpha(StudentList *stuList, StudentType *stu) {
  //Making a stuNode
  StudentNode *stuNode = malloc(sizeof(StudentNode));
  stuNode->data = stu;
  stuNode->next = NULL;
  
  //If the list is empty
  if(stuList->head == NULL){
    stuList->head = stuNode;
	return C_OK;
  //If the stuNode belongs before head
  }else if(strcmp(stu->basicInfo.last,stuList->head->data->basicInfo.last) < 0){
	stuNode->next = stuList->head;
	stuList->head = stuNode;
	return C_OK;
  }

  //Search in between elements
  StudentNode *traverseNode = stuList->head;
  while(traverseNode->next != NULL){
    if(strcmp(stu->basicInfo.last,stuList->head->data->basicInfo.last) <= 0){
	  stuNode->next = traverseNode->next; 
	  traverseNode->next = stuNode;
	  return C_OK;
	}
	traverseNode = traverseNode->next;
  }

  //If we've reached the end of the list and have not found an insert position, then it must be the tail
  traverseNode->next = stuNode;
  
  return C_OK;
}

int deleteStudent(StudentList *stuList, char *fname, char *lname) {
  //IF THE CURRENT TRAVERSAL LAST NAME IS GREATER THE NAME OF INTEREST BREAK CUZ IT AINT THERE
  
  //IF THE HEAD IS TO BE REMOVED
  StudentNode *traverseNode = stuList->head;

  if(checkAlphabet(traverseNode, lname) == C_OK){
	return C_NOK;
  }

  if(strcmp(traverseNode->data->basicInfo.first, fname) == 0 && strcmp(traverseNode->data->basicInfo.last, lname) == 0){
		free(stuList->head->data);
		StudentNode *tempFreeNode = stuList->head;
		stuList->head = traverseNode->next;
		free(tempFreeNode);
		return C_OK;
	}


  while(traverseNode->next != NULL){
	if(checkAlphabet(traverseNode, lname) == C_OK){
		return C_NOK;
  	}
	if(strcmp(traverseNode->next->data->basicInfo.first, fname) == 0 && strcmp(traverseNode->next->data->basicInfo.last, lname) == 0){
		free(traverseNode->next->data);
		StudentNode *tempFreeNode = traverseNode->next;
		traverseNode->next = traverseNode->next->next;
		free(tempFreeNode);
		return C_OK;
	}
	traverseNode = traverseNode->next;
  }

  return C_OK;
}

int cleanupList(StudentList *stuList) {
  StudentNode *tempCleanNode = stuList->head;
  while(stuList->head != NULL){
	free(stuList->head->data);
	tempCleanNode = stuList->head;
	stuList->head = stuList->head->next;
	free(tempCleanNode);	
  }
  free(stuList);
  return C_OK;
}

int checkAlphabet(StudentNode *currentNode, char *lname){
  //If the currentNode is greater than the lname than the elements after the currentNode cannot be less than lname, thus we return
  if(strcmp(currentNode->data->basicInfo.last, lname) > 0){
	return C_OK;
  }
  return C_NOK;

}
