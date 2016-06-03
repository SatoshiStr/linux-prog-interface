#define _XOPEN_SOURCE

#include <pwd.h>
#include <grp.h>

#include <unistd.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
void err() {
	printf("E:\n");
}

char *usernameFromUid(uid_t uid) {
	errno = 0;
	struct passwd *ptr;
	ptr = getpwuid(uid);
	if(ptr == NULL) {
		if(errno == 0)
			return NULL;
		else
			err();
	}
	return ptr->pw_name;
}

uid_t uidFromUsername(char *name) {
	struct passwd *ptr;
	if(name == NULL) return -1;
	ptr = getpwnam(name);
	if(ptr == NULL) {
		return -1;
	}
	return ptr->pw_uid;
}

void traverse() {
	struct passwd *pw;
	pw = getpwent();
	while(pw != NULL) {
		printf("%s %d\n", pw->pw_name, pw->pw_uid);
		pw = getpwent();
	}
	endpwent();
}
//char *crypt(const char *key, const char *salt);
void cryp() {
	char *ptr = crypt("hellodoggg", "ac");
	printf("%s %s\n", ptr, crypt("hellodoggggggg", "ac"));
}
int main(int argc, char *argv[]) {
	//traverse();
	cryp();
}














