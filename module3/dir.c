#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>


int main ( int argc, char **argv)
{
DIR *pdir;
struct dirent *pent;


pdir=opendir(argv[1]);

pent=readdir(pdir);

while (pent != NULL)
	{
	printf("%s\n",pent->d_name);
	pent=readdir(pdir);
	} 
return 0;
}


 
