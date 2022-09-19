#include <stdio.h>


int main(void){
    int gcd(int,int);
    int greatestCommonDivisor = gcd(32,16);
    printf("%d\n", greatestCommonDivisor);
    return 0;
}


int gcd(int a, int b){
    int smallestInt = (a<b) ? a : b;
    int greatestCommon = 1;
    for(int i = 1; i<=smallestInt; i++){
        if(a%i==0 && b%i==0){
            greatestCommon = i;
        }
    }
    return greatestCommon;

}


