#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void err() {
	printf("err\n");
}
void printbr(char *msg) {
	void *br = sbrk(0);
	printf("%s: %llx\n", msg, (long long)br);
}
int main() {
	printbr("start");
	int i = 0;
	char *arr[1000];
	for( ; i < 1000; ++i) {
		arr[i] = malloc(1000);
		if(i % 70 == 0)
			printbr("malloc");
	}
	for(i = 999; i >= 0; --i) {
		free(arr[i]);
		if(i % 70 == 0)
			printbr("free");
	}
}
