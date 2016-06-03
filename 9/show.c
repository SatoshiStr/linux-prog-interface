#include <pwd.h>
#include <grp.h>

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
void err() {
	printf("E:\n");
}

int main() {
	int rid, eid, sid;
	if(getresuid(&rid, &eid, &sid))
		err();
	printf("%d %d %d\n", rid, eid, sid);
	if(getresgid(&rid, &eid, &sid))
		err();
	printf("%d %d %d\n", rid, eid, sid);
	int len = getgroups(0, NULL);
	if(len == -1)
		err();
	gid_t *list = malloc(len);
	if(list == NULL)
		err();
	if(getgroups(len, list) == -1)
		err();
	int i = 0;
	for (; i < len; ++i)
		printf("%d ", list[i]);
	printf("\n");
}
