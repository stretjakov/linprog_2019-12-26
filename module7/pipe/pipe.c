#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>
#define BUF_SIZE 1024
#define SIZE 1048576

int main (int argc, char* argv[])
{
	struct stat fileinfo;
	int fd,fs,i=0,mem=0,n,m=0,size=0,err;
	int fp[2];
	void *memory;
	char string[BUF_SIZE+10];
	char string1[BUF_SIZE+10];
	pid_t pid;

	fd=open(argv[1],O_RDONLY);
	//printf("fd=%d\n",fd);
	if (fd == -1)
       	{
	       perror("open file %s\n",argv[1]);
	       abort();
	}

	err=pipe(fp);
	//printf("1 %d %d\n",fp[0],fp[1]);
	if (err == -1) {perror("Pipe\n"); abort();}
	pid=fork();
	if (pid == -1) {perror("Fork\n"); abort();}
	if (pid != 0)
	{
	//	printf("2 %d %d\n",fp[0],fp[1]);
		close(fp[0]);
	//	printf("3 %d %d\n",fp[0],fp[1]);
		do
		{
			n=read(fd,string,BUF_SIZE);
	//		printf("FD n=%d\n",n);
			if (n==0) break;
	//		printf("%s\n",string);
			write(fp[1],string,n);
		} while (1);
		close(fd);

//		wait(NULL);
		close(fp[1]);
	}
	else
	{
	//	printf("4 %d %d\n",fp[0],fp[1]);
		close(fp[1]);
	//	printf("5 %d %d\n",fp[0],fp[1]);
		do 
		{
		n=read(fp[0],string1,BUF_SIZE);
	//	printf("Child read %d bytes\n",n);
	//	printf("%s\n",string1);
		size=size+n;
		if (size >= SIZE)
			{
			m=m+1;
			printf("Get %d \n",m);
			size=size-SIZE;
			}
		} while ( n != 0);
		close(fp[0]);
		exit(0);
	}
	
	
	return 0;
}
