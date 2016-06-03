#include <setjmp.h>
#include <stdio.h>

static jmp_buf env;

int dojump(int a, int b) {
	printf("%d, %d\n", a, b);
	longjmp(env, 1);
}

int dojump2(int a, int b) {
	printf("%d, %d\n", a, b);
	longjmp(env, 2);
}

int main() {
	volatile int a = 111, b = 222;
	switch(setjmp(env)) {
	case 0:
		a = 333;
		b = 444;
		printf("first ret: %d, %d\n", a, b);
		dojump(a, b);
		break;
	case 1:
		printf("back from 1: %d, %d\n", a, b);
		break;
	case 2:
		printf("back from 2\n");
		break;
	}
	return 1;
}











