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

    //If there was no error & there exists atleast 1 entry print the data unsorted & sorted for comparison
	if(arrayCounter>0){
		printf("\n\tUNSORTED");
		printEmfData(uuidData, emfData, arrayCounter);	
		orderEmfData(uuidData, emfData, arrayCounter);
		printf("\n\tSORTED");
		printEmfData(uuidData, emfData, arrayCounter);	
	}
	
	return(0);
}

/***********************************************************************************************************************************************************************************
 * Description: Retrieves Emf and Uuid Data from the user until they either reach the max entries, or they enter an error, or they enter -1 for either values of the emf and uuid
 * Parameters: Both uuid & emf are output only parameters, because, they only are written to and never read
 * Return: Returns and integer of the valid entries that have been entered into the array
 ***********************************************************************************************************************************************************************************/
int getEmfData(int* uuid, float* emf){
	int currentUuid = 0;
	float currentEmf = 0;
	int arrayCounter = 0;
	
	printf("\t1. Enter an integer between 32850000 & 32859999 for the UUID value\n\t2. Enter a float between 0.0 & 5.0 for the EMF value\n\t3. Both values should be entered on the same line with a single space in between\n\n");	

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


/*****************************************************************************************************************************************************************************************************************
 * Description: Prints all valid data (Includes, emf & uuid) to the terminal
 * Parameters: All these are input parameters. uuid is used to print the values within the uuid array, emf is use to print the values in the emf array, and num is used to track the valid entries of both arrays
 * Return: Returns a void
 *****************************************************************************************************************************************************************************************************************/
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


/********************************************************************************************************************************************************************************************
 * Description: Orders the emf data in decending order
 * Parameters: uuid & emf are input & output variables because they are being read and written to, whereas num is only an input variable because it is only used to track the valid entries.
 * Return: Returns an int to indicate no error has occured
 *********************************************************************************************************************************************************************************************/
int orderEmfData(int* uuid, float* emf, int num){
	if(num <=0){
		return C_ERR_BAD_ARR;
	}

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
		
		//Set the current index of both arrays to the max index of the local arrays
		emf[i] = localEmf[currentHighestEmfIndex];
		uuid[i] = localUuid[currentHighestEmfIndex];

		//Set the currentHighestEmfIndex to -1 to prevent the same max value from being selected
		localEmf[currentHighestEmfIndex] = -1;
	}
	return C_OK;
}

/******************************************************************************************************
 * Description: Determines whether a given uuid is valid or not
 * Parameters:	uuid is an input parameter because it is only used as information and never written to
 * Return:i		Returns an integer which corresponds to an error code
 *****************************************************************************************************/
int validateUUID(int uuid){	
	return (uuid >= 32850000 && uuid <= 32859999) ? C_OK : C_ERR_BAD_UUID;
}

/****************************************************************************************************
 * Description: Determines whether a given emf is valid or not
 * Parameters:	emf is an input parameter because it is only used as information and never written to
 * Return:		Returns an integer which corresponds to an error code
 ****************************************************************************************************/
int validateEMF(float emf){
	return (emf >= 0.0 && emf <= 5.0) ? C_OK : C_ERR_BAD_EMF;
}

/****************************************************************************
 * Description: Prints an error message depending on the value of val
 * Parameters:	val is an input parameter and is used to determine the error
 * Return:		Does not return because it is a void
 ****************************************************************************/
void printErrorMsg(int val){
	//Switch which determines the error code printed
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

/************************************************************************************************************
 * Description: Finds the maximum index of an array
 * Parameters:	emf & emfSize are both input parameters where emfSize is the valid entries of the array emf
 * Return:		An integer which represents the max index of a particular array 
 ************************************************************************************************************/
int findMaxIndex(float* emf, int emfSize){
	int maxIndex = 0;
	
	for(int i = 0; i<emfSize; i++){
		//If the value at the current emf index is greater than the emf at maxIndex, set the maxIndex to the current index
		if(emf[i] > emf[maxIndex]){
			maxIndex = i;
		}
	}
	//Finally return the max index after we've iterated through the entire array
	return maxIndex;
}
