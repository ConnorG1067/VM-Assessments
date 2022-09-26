#include <stdio.h>

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
void printBits(unsigned char);
void printIntBits(int);


int main() {

  unsigned char a = 'A';

  unsigned char arr[2][3][4] = {
                                  {
                                    {62,138,241,129},
                                    {8,221,163,159},
                                    {91,158,169,150}
                                 },
                                  {
                                    {15,138,251,198},
                                    {14,211,161,158},
                                    {77,204,188,217}
                                  }
                                };

  int i, j, k;

  printBits(a);
  a = setBit(a, 2);
  a = setBit(a, 3);
  printBits(a);
  a = clearBit(a, 2);
  printBits(a);
  printf("\n");

  //Calling printIntBits on 82
  printIntBits(82);

  return 0;
}


unsigned char getBit(unsigned char c, int n) {
   return (c & (1 << n)) >> n;
}

unsigned char setBit(unsigned char c, int n) {
    return c | (1 << n);
}

unsigned char clearBit(unsigned char c, int n) {
    return c & (~(1 << n));
}

//Prints the bits of an unsigned char
void printBits(unsigned char c) {
    int bits[8];
    int cAsInt = (int) c;
    //Converting from decimal to binary and storing in an array
    for(int i = 7; i>=0; i--){
        bits[i] = (cAsInt%2>0) ? 1 : 0;
        cAsInt/=2;
    }
    
    //Prints the bits for the user from the array
    for(int i = 0; i< 8; i++){
        printf("%d", bits[i]);

    }
    printf("\n");
}


//Same function as above, but using an int rather than an unsigned char
void printIntBits(int n){
    int bits[8];
    int changableN = n;
    for(int i = 7; i>=0; i--){
        bits[i] = (changableN%2>0) ? 1 : 0;
        changableN/=2;
    }
    

    printf("Decimal To Binary %d\n", n);
    for(int i = 0; i< 8; i++){
        printf("%d", bits[i]);

    }
    printf("\n");
}

