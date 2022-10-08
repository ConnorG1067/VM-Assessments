#include <stdio.h>
#include <string.h>

#define MAX_BUF  256

#define IV  0b10110001
#define KEY 0b11001011
#define CTR 0b00110101

void encode(unsigned char*, unsigned char*, int);
void decode(unsigned char*, unsigned char*, int);

unsigned char processCtr(unsigned char, unsigned char);
unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);

int main()
{
  char str[8];
  int  choice;
	
  //Creating two message arrays with a size of MAX_BUF
  unsigned char plainMsg[MAX_BUF];
  unsigned char cipherMsg[MAX_BUF];

  //Prompting the user
  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("  (0) Exit\n");
  printf("\n  what is your selection: ");

  //Getting user input
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);

  if (choice == 0)
    return 0;

  switch (choice) {
    case 1:
	  //If the user chooses to encrypt
	  fgets(plainMsg, sizeof(plainMsg), stdin);
      encode(plainMsg, cipherMsg, sizeof(plainMsg));
	
	  //Prints the cipher text
	  int i = 0;
      printf("  Encrypted Message:  \n");
	  do{
		printf("%u ", cipherMsg[i]);
		i++;
	  }while(plainMsg[i+1] != '\0');

      break;
    case 2:
	  //If the user chooses to decrypt
	  printf("\n  Use \"-1\" to end your message to decrypt:\n  ");

	  //Counter for the values in the array
	  int arrayCounter = 0;
	  //The variable for the current user input
	  unsigned currentValue;

	  //Scan for user input until currentValue is -1
	  while(1){
		scanf("%u", &currentValue);
		if(currentValue == -1){
			break;
		}
		//Each iteration add currentValue to the cipherMsg array, provided the value is not -1
		cipherMsg[arrayCounter++] = currentValue; 	
	  }
	  //Decode the users cipherMsg
      decode(cipherMsg, plainMsg, arrayCounter);
	  
	  //Prints the plain text
      printf("\n  Decrypted Message:\n  ");
	  for(int i = 0; i<arrayCounter; i++){
		printf("%c", plainMsg[i]);
	  }
	  

      break;
  }

  printf("\n");
  return(0);
}




/* Function:   getBit
    Purpose:   retrieve value of bit at specified position
         in:   character from which a bit will be returned
         in:   position of bit to be returned
     return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n){
	return (c & (1 << n)) >> n;
}

/* Function:   setBit
    Purpose:   set specified bit to 1
         in:   character in which a bit will be set to 1
         in:   position of bit to be set to 1
     return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n){
	return c = c | (1 << n);
}

/* Function:   clearBit
    Purpose:   set specified bit to 0
         in:   character in which a bit will be set to 0
         in:   position of bit to be set to 0
     return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n){
	return c & (~(1 << n));
}

/* Function:   processCtr
    Purpose:   processes the counter variable in encode/decode
         in:   ctr represents the counter value
         in:   key represents the key to decrypt/encrypt the bytes
	 return:   returns the updated counter value 
*/
unsigned char processCtr(unsigned char ctr, unsigned char key){
	int tempCounter = ctr;
	//Start at position 0 is tempCounter is even otherwise, start at 0
	for(int i = tempCounter%2; i<8; i+=2){
        int xorVal = getBit(ctr, i)^getBit(key, i);
		//If xorVal is 0 clear the bit at the ith position, otherwise, set the bit at the ith position to 1
		tempCounter = (xorVal == 0) ? clearBit(tempCounter, i) : setBit(tempCounter,i);
	} 
	return tempCounter;
}

/* Function:   encryptByte
    Purpose:   Takes in a plaintext byte and returns the ciphertext byte
         in:   pt represents the cipher text array
         in:   ctr represents the current counter value
	     in:   prev represents the previous ciphertext byte
	 return:   the encrypted byte as an unsigned char
*/
unsigned char encryptByte(unsigned char pt, unsigned char ctr, unsigned char prev){
	int tempByte = 0;
	//Loop through all bits
	for(int i = 0; i<8; i++){
		//If the bit at the ith position is 1 xor the pt and prev bit at the ith position
		if(getBit(ctr, i) == 1){
            int xorVal = getBit(pt, i)^getBit(prev, i);
			tempByte = (xorVal == 0) ? clearBit(tempByte, i) : setBit(tempByte, i);
		//If the bit at the ith position is 0 xor the pt and prev mirror bit at the ith position
		}else{
            int xorVal = getBit(pt, i)^getBit(prev, 7-i);
			tempByte = (xorVal == 0) ? clearBit(tempByte, i) : setBit(tempByte, i);
        }
	}
	//Return the encrypted byte
	return tempByte;
}

/* Function:   decryptByte
    Purpose:   Takes in a ciphertext byte and returns the plaintext byte
         in:   ct represents the cipher text array
         in:   pt represents the plain text array
	     in:   prev represents the previous ciphertext byte
	 return:   the decrypted byte as an unsigned char
*/
unsigned char decryptByte(unsigned char ct, unsigned char ctr, unsigned char prev){
	int tempByte = 0;
	//Loop through all bits
	for(int i = 0; i<8; i++){
		//If the bit at the ith position is 1 xor the ct and prev bit at the ith position
		if(getBit(ctr, i) == 1){
            int xorVal = getBit(ct, i)^getBit(prev, i);
			tempByte = (xorVal == 0) ? clearBit(tempByte, i) : setBit(tempByte, i);
		//If the bit at the ith position is 0 xor the ct and prev mirror bit at the ith position
		}else{
            int xorVal = getBit(ct, i)^getBit(prev, 7-i);
			tempByte = (xorVal == 0) ? clearBit(tempByte, i) : setBit(tempByte, i);
        }
	}
	//Return the decrypted byte
	return tempByte;
}

/* Function:   encode
    Purpose:   Makes use of processCtr & encryptByte to encrypt user input
     in/out:   ct represents the cipher text array
     in/out:   pt represents the plain text array
	     in:   numBytes is the amount of bytes the user has entered
	 return:   void
*/
void encode(unsigned char* pt, unsigned char* ct, int numBytes){
	//Create a counter variable to populate the cipher text array
    int i = 0; 
	//Create a counter variable for the counter used for the encryption/decryption algorithm
    int counter = CTR;

    do{
		//Process the counter
		counter = processCtr(counter, KEY);
		//Set the current cipher text position to the value retrieved from encryptByte
		//If this is the first iteration use IV otherwise use the previous cipher text byte
        ct[i] = encryptByte(pt[i], counter, (i == 0) ? IV : ct[i-1]);
		//Increment the counter and i
        counter++;
        i++;
    }while(i<numBytes);
}

/* Function:   decode
    Purpose:   Makes use of processCtr & decryptByte to decrypt user input
     in/out:   ct represents the cipher text array
     in/out:   pt represents the plain text array
	     in:   numBytes is the amount of bytes the user has entered
	 return:   void
*/
void decode(unsigned char *ct, unsigned char *pt, int numBytes){
	//Create a counter variable to populate the plain text array
	int i = 0; 
	//Create a counter variable for the counter used for the encryption/decryption algorithm
    int counter = CTR;

    do{
		//Process the counter
		counter = processCtr(counter, KEY);
		//Set the current plain text position to the value retrieved from decryptByte
		//If this is the first iteration use IV otherwise use the previous cipher text byte
        pt[i] = decryptByte(ct[i], counter, (i == 0) ? IV : ct[i-1]);	
		//Increment the counter and i
        counter++;
        i++;
    }while(i < numBytes);
}


