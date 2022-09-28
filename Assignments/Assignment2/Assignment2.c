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

	  fgets(encryptMsg, sizeof(encryptMsg), stdin);
	  processCtr(CTR, KEY);
	  
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
	printf("%d\n", tempCounter);
	for(int i = (tempCounter%2 == 0) ? 0 : 1; i < 7; i+=2){
		tempCounter = setBit(getBit(ctr, i)^getBit(key, i), i);
		printf("%u\n",setBit(getBit(ctr, i)^getBit(key, i), i));
	}

	return tempCounter;
}
//Ctr = counter, pt = plain text, prev = previous 
unsigned char encryptByte(unsigned char pt, unsigned char ctr, unsigned char prev){
	int tempByte = 0;

	for(int i = 0; i<7; i++){
		if(getBit(ctr, i) == 1){
			tempByte = setBit(getBit(pt, i)^getBit(prev, i), i);
		}else{
			tempByte = setBit(getBit(pt, i) ^ getBit(prev, 7-i), i);
		}
	}
	return tempByte;
}

void encode(unsigned char* pt, unsigned char* ct, int numBytes){

}
