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


  for(int i = 0; i<2; i++){
        for(int j = 0; j<3; j++){
            for(int k = 0; k<3; k++){
                printBits(arr[i][j][k]);
                arr[i][j][k] = clearBit(arr[i][j][k], 6);
                arr[i][j][k] = setBit(arr[i][j][k], 3);
                printBits(arr[i][j][k]);
                printf("\n");
            }
        }

  }

  //Calling printIntBits on 82
  printf("\n82 as binary\n");
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
    //Converting from decimal to binary and storing in an array
    for(int i = 7; i>=0; i--){
      printf("%d", getBit((int) c, i)); 
    }
    printf("\n");
    
}


//Same function as above, but using an int rather than an unsigned char
void printIntBits(int n){
    //Converting from decimal to binary and storing in an array
    for(int i = 7; i>=0; i--){
      printf("%d", getBit(n, i)); 
    }
    printf("\n");
}

