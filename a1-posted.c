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


int main()
{

  return(0);
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
