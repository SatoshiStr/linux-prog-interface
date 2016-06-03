#include <pwd.h>
#include <grp.h>

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <limits.h>

void err() {
	printf("E:%s\n", strerror(errno));
}

int myinitgroups(const char *user, gid_t gid) {
	gid_t arr[NGROUPS_MAX + 1];
	int index = 0;
	struct group *grp;
	while((grp = getgrent()) != NULL) {
		char **mp = grp->gr_mem;
		int inside = 0;
		while(*mp != NULL) {
			if(strcmp(*mp, user) == 0) {
				inside = 1;
				break;
			}
			mp++;
		}
		if(inside)
			arr[index++] = grp->gr_gid;
	}
	arr[index++] = gid;
	if(setgroups(index, arr))
		err();
	return 0;
}

int main() {
	myinitgroups("roger", 3);
	int len = getgroups(0, NULL);
	if(len == -1)
		err();
	gid_t *list = malloc(len);
	if(getgroups(len, list) == -1)
		err();
	int i = 0;
	for (; i < len; ++i)
		printf("%d ", list[i]);
	printf("\n");
}

