#include <stdio.h>

void encryptCaesar(char*, unsigned char);
void decryptCaesar(char*, unsigned char);
void toUpper(char*);

int main() {
  char plain[] = "Friends, Romans, countrymen, lend me your ears";
  char cipher[] = "Mvez, mzuz, mztz (Z trdv, Z jrn, Z tfehlvivu)";

  printf("%s\n", plain);
  toUpper(plain);
  printf("%s\n", plain);
  encryptCaesar(plain, 5);
  printf("%s\n", plain);
  decryptCaesar(plain, 5);
  printf("%s\n", plain);

  return 0;
}

void toUpper(char *text) {
  int i = 0;
  while (text[i] != '\0') {
    if (text[i] >= 'a' && text[i] <= 'z') {
      text[i] -= 32;
    }
    i++;
  }
}

void encryptCaesar(char *plaintext, unsigned char key) {
  toUpper(plaintext);
  int i = 0;
  while (plaintext[i]!='\0'){
    if(plaintext[i] > 85){
        plaintext[i] = ((plaintext[i]+key) % 90)+64;
    }else if(plaintext[i]>=65 && plaintext[i]<=90){
        plaintext[i] += key;
    }
    i++;
  } 
}

void decryptCaesar(char *ciphertext, unsigned char key) {
  toUpper(ciphertext);
  int i = 0;
  while (ciphertext[i]!='\0'){
    if(ciphertext[i] < 69 && ciphertext[i] >=65){
        printf("%d\n", (ciphertext[i]-key));
        ciphertext[i] = 90-((ciphertext[i]-key) % 65);
    }else if(ciphertext[i]>=65 && ciphertext[i]<=90){
        ciphertext[i] -= key;
    }
    i++;
  } 


}
