#include <stdio.h>

int gcd(int,int);

int main(void){

    for(int i = 1; i<15; i++){
        for(int j = 1; j<15; j++){
            int greatestCommonDivisor = gcd(i,j);
            printf("GCD for numbers %d, %d: %d\n",i,j,greatestCommonDivisor);   
        }
    }
    return 0;
}


int gcd(int a, int b){
    //Finds smallest value between the two values
    int smallestInt = (a<b) ? a : b;
    //Sets the current greatest common divisor to 1
    int greatestCommon = 1;
    for(int i = 1; i<=smallestInt; i++){
        //If both have no remainder then it is considered a GCD
        if(a%i==0 && b%i==0){
            greatestCommon = i;
        }
    }

    return greatestCommon;

}


