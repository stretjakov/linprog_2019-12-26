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
	int fd,fs,i=0,mem=0,n,m=0,size=0,err;
	int fp;
	char string[BUF_SIZE+10];
	pid_t pid;

	fp=open(argv[1],O_WRONLY);
	if (fp == -1)
       	{
	       perror("open pipe %s\n",argv[1]);
	       abort();
	}
	fd=open(argv[2],O_RDONLY);
	if (fd == -1)
       	{
	       perror("open file %s\n",argv[2]);
	       abort();
	}

	do
	{
	n=read(fd,string,BUF_SIZE);
	if (n==0) break;
	write(fp,string,n);
	} while (1);
	close(fd);
	close(fp);
	
return 0;
}
