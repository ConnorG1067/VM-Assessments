#include <stdio.h>

//Constants
#define MAX_SIZE  32
#define C_OK             0	// Success flag
#define C_ERR_ARR_FULL  -1	// Error code for array is full
#define C_ERR_BAD_EMF   -2	// Error code for an invalid EMF value
#define C_ERR_BAD_UUID  -3	// Error code for an invalid UUID value
#define C_ERR_BAD_ARR   -4	// Error code for an array error

//Function Declarations
int  getEmfData(int*, float*);
void printEmfData(int*, float*, int);
int  orderEmfData(int*, float*, int);

int  validateUUID(int);
int  validateEMF(float);
void printErrorMsg(int);      
int  findMaxIndex(float*, int);


int main(){
	//Create two arrays of max size, one for the uuid & the other for the emf
	int uuidData[MAX_SIZE];
  	float emfData[MAX_SIZE];
	//Only one counter is needed because the arrays are synchronized
    //Call the function getEmfData to and store the returned in in arrayCounter variable
	int arrayCounter = getEmfData(uuidData, emfData);
	//Print the error message of the array counter, provided there is an error
    printErrorMsg(arrayCounter);

    //If there was no error print the data un sorted & sorted for comparison
	if(arrayCounter>=0){
		printf("\n\tUNSORTED");
		printEmfData(uuidData, emfData, arrayCounter);	
	

		orderEmfData(uuidData, emfData, arrayCounter);
		printf("\n\tSORTED");
		printEmfData(uuidData, emfData, arrayCounter);	
	}
	
	return(0);
}

/*
 * Description:
 * Parameters
 * Return:
 */
int getEmfData(int* uuid, float* emf){
	int currentUuid = 0;
	float currentEmf = 0;
	int arrayCounter = 0;

	printf("\t------------------------------------------------------------------------------------------\n");
		printf("\t| 1. Enter an integer between 32850000 & 32859999 for the UUID value%22s\n\t| 2. Enter a float between 0.0 & 5.0 for the EMF value%36s\n\t| 3. Both values should be entered on the same line with a single space in between%8s\n","|", "|", "|");	
		printf("\t------------------------------------------------------------------------------------------\n\n");

	do{
	
		printf("\tEntry #%d: ", arrayCounter+1);
		scanf("%d %f", &currentUuid, &currentEmf);
	
		if(validateUUID(currentUuid) == 0 && validateEMF(currentEmf) == 0 && arrayCounter<MAX_SIZE){
			uuid[arrayCounter] = currentUuid;
			emf[arrayCounter++] = currentEmf;
		}else if (arrayCounter>=MAX_SIZE){
			return C_ERR_ARR_FULL;
		}else if(currentUuid != -1 && validateUUID(currentUuid) == C_ERR_BAD_UUID){
			return C_ERR_BAD_UUID;
		}else if(currentEmf != -1 && validateEMF(currentEmf)){
			return C_ERR_BAD_EMF;
		}
	}while(currentUuid != -1 && currentEmf != -1);


	return arrayCounter;

	
}

void printEmfData(int* uuid, float* emf, int num){

	printf("\n\t----------------------------\n");	
	printf("\t|UUID%19sEMF|\n", "");
	printf("\t|%26s|\n", "");
	for(int i = 0; i<num; i++){
		printf("\t|%8d%15s%0.1f|\n", uuid[i], "",emf[i]);
	}
	printf("\t----------------------------\n");
	printf("\tTotal Pairs: %*s%d\n", (num<10) ? 14 : 13 ,"",num);
}

int orderEmfData(int* uuid, float* emf, int num){
	int localUuid[num];
	float localEmf[num];

	//deep copy both arrays
	for(int i = 0; i<num; i++){
		localUuid[i] = uuid[i];
		localEmf[i] = emf[i];
	}
	
	for(int i = 0; i<num; i++){

		//Find the highest index
		int currentHighestEmfIndex = findMaxIndex(localEmf, num);

		emf[i] = localEmf[currentHighestEmfIndex];
		uuid[i] = localUuid[currentHighestEmfIndex];

		localEmf[currentHighestEmfIndex] = -1;
	}
	
	return C_OK;
}

int validateUUID(int uuid){	
	return (uuid >= 32850000 && uuid <= 32859999) ? C_OK : C_ERR_BAD_UUID;
}

int validateEMF(float emf){
	return (emf >= 0.0 && emf <= 5.0) ? C_OK : C_ERR_BAD_EMF;
}

void printErrorMsg(int val){
    switch(val){
        case C_ERR_ARR_FULL:
            printf("\n\tError: You've reached the maximum number of entries\n");
            break;
        case C_ERR_BAD_UUID:
            printf("\n\tError: Invalid UUID!\n\n");
            break;
        case C_ERR_BAD_EMF:
            printf("\n\tError: Invalid EMF!\n\n");
            break;
		default:
			break;


    }
}

//Find the index which corresponds to the largest element
int findMaxIndex(float* emf, int emfSize){
	int maxIndex = 0;
	for(int i = 0; i<emfSize; i++){
		if(emf[i] > emf[maxIndex]){
			maxIndex = i;
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
