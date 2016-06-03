
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void err() {
	printf("err\n");
	exit(-1);
}
int mysetenv(char *name, char *value, int overwrite) {
	int found;
	if(getenv(name) == NULL) {
		found = 0;
	} else {
	 	found = 1;
	}
	if(found && overwrite == 0) {
		return 0;
	}
	if(putenv(name) != 0)  // delete pre
		return -1;
	int len = strlen(name) + strlen(value) + 2;
	char *buf = malloc(len);
	if(buf == NULL)
		return -1;
	strcpy(buf, name);
	strcpy(buf + strlen(name), "=");
	strcpy(buf + strlen(name) + 1, value);
	if(putenv(buf) != 0)
		return -1;
	//free(buf);
	return 0;
}
int myunsetenv(char *name) {
	if(putenv(name) != 0)
		return -1;
	return 0;
}

extern char **environ;
int main() {
	clearenv();
	if(mysetenv("a", "hh", 0))
		err();
	if(mysetenv("a", "over", 1))
		err();
	if(mysetenv("b", "hh", 0))
		err();
	//
	char a[] = "k=a", b[] = "m=b";
	if(putenv(a))
		err();
	if(putenv(b) != 0)
		err();
	a[0] = 'm';
	myunsetenv("m");
	char **ep = environ;
	for(; *ep != NULL; ++ep)
		printf("%s\n", *ep);
}





