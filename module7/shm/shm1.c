#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define BUF_SIZE 1024
#define SIZE 1048576

int main (int argc, char* argv[])
{
	int fd,i=0,n,m=0,size=0,err,id;
	char string[BUF_SIZE+10];
	char *shared_memory, *p;
	key_t key1;
	key1=ftok("/home/user1",'s');
	
	fd=open(argv[1],O_RDONLY);
	if (fd == -1)
       	{
	       perror("open file %s\n",argv[1]);
	       abort();
	}
	
	id=shmget(key1,BUF_SIZE, IPC_CREAT | 0666);
		
	if (id == -1)
	{
		perror("Error");
		abort();
	}
	
	shared_memory=(char*) shmat(id,0,0);
			
	do
	{
		n=read(fd,string,BUF_SIZE);
		printf ("N=%d\n",n); 
		if (n==0) break;
		snprintf(shared_memory,n,"%s",string);
	} while (1);
	shmdt(shared_memory);
//	msgctl(id,IPC_RMID,0);
	
	return 0;
}
