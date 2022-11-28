#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>

void handleChildSig1(int);
void handleChildSig2(int);

int main(int argc, char* argv[])
{
  int a = fork();
  printf("%d: %s\n", a, (a!=0) ? "Child\n" :  "Parent\n");
  
  sleep(1);
  if(a == 0){
	signal(SIGUSR1, handleChildSig1);
    signal(SIGUSR2, handleChildSig2);
  }
  	
  int choice, pid;

  int running = 1;

  if(a != 0){
	while(running){
		printf("CHOICE (0-2): ");
		scanf("%d", &choice);
		if(choice == 1){
			kill(a, SIGUSR1);
		}else if(choice == 2){
			kill(a, SIGUSR2);
		}else if(choice == 0){
			kill(a, SIGINT);
			running = 0;
		}
		sleep(1);
	}

  }

  while(1 && running){
	sleep(1);
  }

}


void handleChildSig1(int i){
	printf("\nReceived SIGUSR1\n");
}

void handleChildSig2(int i){
	printf("\nReceived SIGUSR2\n");
}
