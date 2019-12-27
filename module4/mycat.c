
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/mman.h>

#define LEN 4096*10


int main ( int argc, char **argv)
{
void *buf;
int fd;
int len=LEN,len_end;
struct stat st;
int num;
off_t off;
int i,n,code,pg;

pg=getpagesize();
printf("page size=%d\n",pg);

fd=open(argv[1], O_RDONLY);

fstat(fd, &st);
printf("file %s has size=%ld bytes\n",argv[1], (long)(st.st_size));

num=(int)((long)st.st_size/(long)len);
len_end=(int)( (long)st.st_size-(long)num*(long)len);

printf("num=%d len_end=%d\n", num,len_end);

for (i=1,off=0; i <=num; i++,off+=len)
	{
	buf=mmap(0,(size_t)len,PROT_READ,MAP_PRIVATE,fd,off);
	if (buf == MAP_FAILED) perror ("MMap error\n");
	n=write(2, buf, len);
	printf("off=%ld n=%d\n", (long) off,n);
	code=munmap(buf,(size_t) len);
	if (code == -1 ) perror ("unmap error\n");
	}

buf=mmap(0,(size_t)len_end, PROT_READ,MAP_PRIVATE,fd,off);
printf("buf=%p\n",buf);
if (buf == MAP_FAILED) perror ("mmap error\n");
n=write(2, buf, len_end);
printf("off=%ld n=%d\n", (long) off,n);
munmap(buf,(size_t) len_end);
close(fd);



return 0;
}


 
