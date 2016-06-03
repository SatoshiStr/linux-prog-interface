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

int main(int argc, char *argv[]) {
	if(argc < 3)
		return ;
	int flags = O_WRONLY | O_CREAT | O_TRUNC;
	if(argc == 4 && argv[3][0] == 'x') {
		int fd = open(argv[1], flags, S_IWUSR | S_IRUSR);
		if(fd == -1)
			err();
		int i = 0, len = atoi(argv[2]);
		off_t offset;
		for(; i < len; ++i) {
			if((offset = lseek(fd, 0, SEEK_END)) == -1)
				err();
			if(write(fd, "x", 1) != 1)
				err();
		}
		if(close(fd))
			err();
	} else {
		// append
		flags |= O_APPEND;
		int fd = open(argv[1], flags, S_IWUSR | S_IRUSR);
		if(fd == -1)
			err();
		int i = 0, len = atoi(argv[2]);
		for(; i < len; ++i) {
			if(write(fd, "x", 1) != 1)
				err();
		}
		if(close(fd))
			err();
	}
	return 0;
	
}



