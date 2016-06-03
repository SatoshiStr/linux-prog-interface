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

int my_dup(int oldfd) {
	// if oldfd valid
	if(fcntl(oldfd, F_GETFL) == -1) {
		return -1;
	}
	return fcntl(oldfd, F_DUPFD, 0);
}
int my_dup2(int oldfd, int newfd) {
	if(oldfd == newfd) {
		return oldfd;
	}
	// valid?
	if(fcntl(oldfd, F_GETFD) == -1)
		return -1;
	if(close(newfd) == -1)
		return -1;
	return fcntl(oldfd, F_DUPFD, newfd);
}
int main() {
	int fd = open("in", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		err();
	}
	int newfd;
	newfd = my_dup(5);
	if(newfd == -1) {
		err();
	}
	printf("my_dup: %d\n", newfd);
	printf("dup21 %d\n", newfd);
	newfd = my_dup2(fd, 1);
	printf("dup2 %d\n", newfd);
	if(newfd == -1)
		err();
	printf("dup22 %d\n", newfd);
	int wno = write(newfd, "hello", 5);
	if(wno != 5)
		err();
	return 0;
}




