#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int err() {
	printf("error: %s\n", strerror(errno));
	fflush(stdout);
	//exit(-1);
}

int main() {
	int fd = open("in", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd == -1)
		err();
	int newfd = dup(fd);
	if(newfd == -1)
		err();
	// same flags
	int flags1 = fcntl(fd, F_GETFL);
	int flags2 = fcntl(fd, F_GETFL);
	if(flags1 == flags2)
		printf("same flags\n");
	else
		err();
	// same offset
	if(write(fd, "hello, ", 7) != 7)
		err();
	if(write(newfd, "world!\n", 7) != 7)
		err();
	return 0;
}




