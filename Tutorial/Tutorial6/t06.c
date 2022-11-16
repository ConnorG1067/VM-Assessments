#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "t06defs.h"

/* Implement StudentNode type */

typedef struct {
  StudentNode *head;
} StudentList;


/* Implement the following functions */
void addStudent(StudentList *, StudentNode *);
void printList(const StudentList *);
void appendStudent(StudentList*, StudentNode*);


int main(void) {
  int i;
  
  StudentType matilda, joe, timmy;
  StudentNode matildaNode, joeNode, timmyNode;

  initStudent("Matilda", "Mallister", 22, "123444555",
              9.0, &matilda);
  initStudent("Joe", "The Plumber", 24, "567888999",
              8.7, &joe);
  initStudent("Timmy", "Tortoise", 99, "345667788",
              11.5, &timmy); 
 
  matildaNode.data = &matilda;
  joeNode.data = &joe;
  timmyNode.data = &timmy;

  StudentList comp2401;

  comp2401.head = NULL;



  addStudent(&comp2401, &matildaNode);
  addStudent(&comp2401, &joeNode);
  addStudent(&comp2401, &timmyNode);

/*
  appendStudent(&comp2401, &matildaNode);
  appendStudent(&comp2401, &joeNode);
  appendStudent(&comp2401, &timmyNode);
*/
  printList(&comp2401);

  return 0;
}

/*   Function:  addStudent                                  */
/*         in:  Location of StudentList to be modified      */
/*         in:  Location of StudentType to be added         */
/*        out:  StudentList with added StudentType          */
/*    Purpose:  adds stu to stuList at the head of the list */
void addStudent(StudentList *stuList, StudentNode *stuNode) {
	stuNode->next = stuList->head;
	stuList->head = stuNode;	
}

void appendStudent(StudentList* stuList, StudentNode* a){
	
	if(stuList->head == NULL){
		stuList->head = a;
		return;
	}

	//Make a dummy pointer to the head
	StudentNode **tempNode = &stuList->head;	
	//Go through until the next element is null meaning, we are currently on the last element
	while((*tempNode)->next != NULL){
		(*tempNode) = (*tempNode)->next;
	}
	//Once found set the next of the current to the studen node
	(*tempNode)->next = a;
}

void printList(const StudentList *stuList) {
	StudentNode *tempNode = stuList->head;
	while(tempNode != NULL){
	    printStudent(tempNode->data);	
		tempNode = tempNode->next;
	}

}
