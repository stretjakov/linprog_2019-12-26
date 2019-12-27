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
	char string1[BUF_SIZE+10];

	fp=open(argv[1],O_RDONLY);
	if (fd == -1)
       	{
	       perror("open pipe %s\n",argv[1]);
	       abort();
	}

	do 
	{
	n=read(fp,string1,BUF_SIZE);
	size=size+n;
	if (size >= SIZE)
		{
		m=m+1;
		printf("Get %d \n",m);
		size=size-SIZE;
		}
	} while ( n != 0);
	close(fp);
	return(0);
}
