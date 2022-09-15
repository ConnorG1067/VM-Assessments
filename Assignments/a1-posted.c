#include <stdio.h>

#define MAX_SIZE  32

#define C_OK             0	// Success flag
#define C_ERR_ARR_FULL  -1	// Error code for array is full
#define C_ERR_BAD_EMF   -2	// Error code for an invalid EMF value
#define C_ERR_BAD_UUID  -3	// Error code for an invalid UUID value
#define C_ERR_BAD_ARR   -4	// Error code for an array error

int  getEmfData(int*, float*);
void printEmfData(int*, float*, int);
int  orderEmfData(int*, float*, int);

int  validateUUID(int);
int  validateEMF(float);
void printErrorMsg(int);        // Hint: Write modular code using helper functions for repeated functionality
int  findMaxIndex(float*, int);


int main(){
	//Keep The two Synchronized 
	int uuidData[MAX_SIZE];
  	float emfData[MAX_SIZE];
	//Only one counter is needed because the arrays are synchronized
	int arrayCounter = getEmfData(uuidData, emfData);


	printEmfData(uuidData, emfData, (arrayCounter>=0)? arrayCounter : 0);	

	return(0);
}


int getEmfData(int* uuid, float* emf){
	int currentUuid = 0;
	float currentEmf = 0;
	int arrayCounter = 0;

	do{

		printf("Enter an integer between 32850000 & 32859999 for the UUID value\nEnter a float between 0.0 & 5.0 for the EMF value\nBoth values should be entered on the same line with a single space in between\t");
		scanf("%d ", &currentUuid);
		scanf("%f", &currentEmf);
	
//Currently exits code on faults	
		if(validateUUID(currentUuid) == 0 && validateEMF(currentEmf) == 0 && arrayCounter<MAX_SIZE){
			uuid[arrayCounter] = currentUuid;
			emf[arrayCounter++] = currentEmf;
		}
		else if (arrayCounter>=MAX_SIZE){
			printErrorMsg(C_ERR_ARR_FULL);
		}else if(validateUUID(currentUuid) == C_ERR_BAD_UUID){
			printErrorMsg(C_ERR_BAD_UUID);
		}else if(validateEMF(currentEmf)){
			printErrorMsg(C_ERR_BAD_EMF);
		}
	}while(currentUuid != -1 && currentEmf != -1);

	
	return arrayCounter;

	
}

void printEmfData(int* uuid, float* emf, int num){
	for(int i = 0; i<num; i++){
		printf("%20d %0.1f\n", uuid[i], emf[i]);
	}
	printf("%12sTotal Pairs:  %d\n", "" ,num);
}

int  orderEmfData(int*, float*, int){

}

int  validateUUID(int uuid){	
	return (uuid >= 32850000 && uuid <= 32859999 && uuid != -1) ? C_OK : C_ERR_BAD_UUID;
}

int  validateEMF(float emf){
	return (emf >= 0.0 && emf <= 5.0 && emf != -1) ? C_OK : C_ERR_BAD_EMF;
}

void printErrorMsg(int val){
    switch(val){
        case C_ERR_ARR_FULL:
            printf("You've reached the maximum number of entries'");
            break;
        case C_ERR_BAD_UUID:
            printf("Invalid UUID!");
            break;
        case C_ERR_BAD_EMF:
            printf("Invalid EMF!");
            break;
        


    }
}

//Find the index which corresponds to the largest element
int findMaxIndex(float* emf, int emfSize){
	int maxIndex = 0;
	for(int i = 0; i<emfSize; i++){
		if(emf[i] > maxIndex){
			maxIndex = emf[i];
		}
	}
	return maxIndex;
}



/***********************************************
 * This and the below comments can be removed
 * but are provided to give you an example of
 * how to write comments for your functions.
***********************************************/
/*  
  Function: myFunction()
  Purpose:  Do that thing this function does
       in:   this is the point of the first parameter
       out:  this is the point of the second parameter
  return:   the thing we're looking for, or C_APPROPRIATE_ERROR if not found
*/
