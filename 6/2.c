#include <setjmp.h>
#include <stdio.h>
static jmp_buf env;
int errjmp() {
	if(setjmp(env) == 0) {
		printf("first errjmp\n");
	} else {
		printf("return by longjmp in errjmp\n");
	}
}

int main() {
	errjmp();
	longjmp(env, 1);
}
