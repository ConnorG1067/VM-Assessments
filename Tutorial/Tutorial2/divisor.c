#include <stdio.h>

int gcd(int,int);

int main(void){
	//TEST VALUES
	printf("GCD of 5 & 3 (expected 1): %d\n", gcd(5,3)); 
	printf("GCD of 3 & 5 (expected 1): %d\n", gcd(3,5)); 
	printf("GCD of 10 & 2 (expected 2): %d\n", gcd(10,2)); 
	printf("GCD of 5 & 5 (expected 5): %d\n", gcd(5,5)); 
	printf("GCD of 6 & 3 (expected 3): %d\n", gcd(6,3)); 
	printf("GCD of 1 & 5 (expected 1): %d\n", gcd(1,5)); 
	printf("GCD of 100 & 10 (expected 10): %d\n", gcd(100,10)); 
	printf("GCD of 1000000 & 100 (expected 100): %d\n", gcd(1000000,100)); 
	printf("GCD of 72 & 4 (expected 4): %d\n", gcd(72, 4)); 
	
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


