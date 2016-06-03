#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void err() {
	printf("err");
	exit(-1);
}
extern char **environ;
int main(int argc, char *argv[]) {
	clearenv();
	if(clearenv())
		err();
	int i;
	for(i = 1; i < argc; ++i) {
		if(putenv(argv[i]))
			err();
	}
	if(setenv("GREET", "hello d", 0))
		err();
	if(unsetenv("BYE"))
		err();
	char **ep = environ;
	for(; *ep != NULL; ++ep)
		printf("%s\n", *ep);
}



