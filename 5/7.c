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
struct vec {
	void *ptr;
	size_t len;
};
void copy(char *src, int len, char *dest) {
	int i = 0;
	for(; i < len; ++i) {
		dest[i] = src[i];
	}
}
ssize_t myreadv(int fd, struct vec *iov, int len) {
	int byteno = 0;
	int i;
	for(i = 0; i < len; ++i)
		byteno += iov[i].len;
	void *buf = malloc(byteno);
	if(buf == NULL)
		err();
	int readno;
	if((readno = read(fd, buf, byteno)) == -1)
		err();
	int writeno = 0;
	i = 0;
	while(writeno < readno) {
		int writelen;
		int left = readno - writeno;
		if(left < iov[i].len)
			writelen = left;
		else
			writelen = iov[i].len;
		copy(buf + writeno, writelen, iov[i].ptr);
		writeno += writelen;
		++i;
	}
	free(buf);
	return readno;
}

int main() {
	int a;
	char str[10] = {0};
	struct vec iov[2] = {{&a, sizeof(a)}, {str, 10}};
	int readno = myreadv(0, iov, 2);
	printf("%d read\n%d %s %s", readno, a, str, (char*)&a);
}




