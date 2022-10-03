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

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("  (0) Exit\n");
  printf("\n  what is your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);

  if (choice == 0)
    return 0;

  switch (choice) {
    case 1:
	  char encryptMsg[100];
      char cipherMsg[100];

	  fgets(encryptMsg, sizeof(encryptMsg), stdin);
        
      encode(encryptMsg, cipherMsg, sizeof(encryptMsg));
      break;

    case 2:

      break;
  }

  return(0);
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
	return (c & (1 << n)) >> n;
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
	return c = c | (1 << n);
}

/*  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
	return c & (~(1 << n));
}


//Processing the counter value
unsigned char processCtr(unsigned char ctr, unsigned char key){
	int tempCounter = ctr;
	for(int i = (tempCounter%2 == 0) ? 0 : 1; i<8; i+=2){
        int xorVal = getBit(ctr, i)^getBit(key, i);
        //printf("%u, %u = %u\n", getBit(ctr, i), getBit(key, i), xorVal);
        //If the xorVal is 0 clear the bit at the position if it is not 0 then set the bit
		tempCounter = (xorVal == 0) ? clearBit(tempCounter, i) : setBit(tempCounter,i);
	} 
	return tempCounter;
}
//Ctr = counter, pt = plain text, prev = previous 
unsigned char encryptByte(unsigned char pt, unsigned char ctr, unsigned char prev){
	int tempByte = 0;

	for(int i = 0; i<7; i++){
		if(getBit(ctr, i) == 1){
            int xorVal = getBit(pt, i)^getBit(prev, i);
			tempByte = (xorVal == 0) ? clearBit(tempByte, i) : setBit(tempByte, i);
		}else{
            int xorVal = getBit(pt, i)^getBit(prev, 7-i);
			tempByte = (xorVal == 0) ? clearBit(tempByte, i) : setBit(tempByte, i);
        }
	}

	return tempByte;
}

void encode(unsigned char* pt, unsigned char* ct, int numBytes){
    int i = 0; 
    int counter = CTR;

    while(pt[i] != '\0'){
        ct[i] = encryptByte(pt[i], counter, (i == 0) ? IV : ct[i-1]);
        printf("%u ", ct[i]);
        counter++;
        i++;
    }


