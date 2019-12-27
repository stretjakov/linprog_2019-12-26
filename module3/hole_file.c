#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main (int argc, char* argv[])
{
	int i, fd;
	int size;
	char Arr[11]="aaaaaaaaaa";
	char Arrb[11]="bbbbbbbbbb";
	
	size=atoi(argv[2]);
	
	fd=open(argv[1],O_CREAT|O_RDWR);
	if (fd==-1)
	{
		perror("Error");
		abort();
	}
	else
	{
		i=write(fd,Arr,10);
		if ( i==-1) perror("write error\n");
		else printf("write %d bytes\n",i);
		lseek(fd,size*1024*1024,SEEK_CUR);
		i=write(fd,Arrb,10);
		if ( i==-1) perror("write error\n");
		else printf("write %d bytes\n",i);
		close(fd);
		
	}
	return 0;
}
