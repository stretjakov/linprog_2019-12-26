#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main (int arg, char* argv[])
{
	int file;
	
	file=open(argv[1],O_CREAT | O_EXCL);

	if (file==-1)
	{
		perror("error\n");
	}
	else
	{
		printf("Open file %s\n",argv[1]);
	}
	
	return 0;
}
