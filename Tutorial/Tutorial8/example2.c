#include <stdio.h>
#include <stdlib.h>

char* convertToOct(int);

int main() {
	int n;
	printf("Enter an integer number:");
	scanf("%d", &n);
	printf("Decimal = %d\n", n);
	char* digits = convertToOct(n);
	int i;
	printf("Octal = ");
	for(int i = 6; i>=0; i--){
		
		printf("%d", digits[i]);
	}
	printf("\n");
	return 0;
}

char* convertToOct(int n) {
	char digits[6];
	int c = 0;
	while (n > 0) {
		digits[c] = n % 8;
		n = n / 8;
		c++;
	}
	for(int i = 2; i>=0; i--){
		
		printf("%c\n", digits[i]);
	}
	char* digitPtr = digits;
	return digitPtr;
}
