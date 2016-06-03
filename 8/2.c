#include <pwd.h>
#include <grp.h>

#include <unistd.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
void err() {
	printf("E:\n");
}

struct passwd * mygetpwname(char *name) {
	struct passwd *pw;
	while((pw = getpwent()) != NULL) {
		if(strcmp(pw->pw_name, name) == 0)
			return pw;
	}
	return NULL;
}

int main() {
	struct passwd *pw = mygetpwname("roger");
	printf("%s %d\n", pw->pw_name, pw->pw_uid);
}


