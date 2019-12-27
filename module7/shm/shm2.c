#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <stdio.h>


#define BUF_SIZE 1024
#define SIZE 1048576

int main (int argc, char* argv[])
{
	int fd,i=0,n,m=0,size=0,err,id;
	char string[BUF_SIZE+10];
	char *shared_memory, *p, c;
	struct shmid_ds shmbuffer;
	int segment_size;
	key_t key1;
	key1=ftok("/home/user1",'s');
	
	id=shmget(key1,2*BUF_SIZE, IPC_CREAT | 0440);
	printf("ID=%d\n",id);
		
	if (id == -1)
	{
		perror("Error");
		abort();
	}
	
	shared_memory=(char*) shmat(id,0,0);
	shmctl (id,IPC_STAT,&shmbuffer);
	segment_size=shmbuffer.shm_segsz;
	
	printf("Segment size=%d\n",segment_size);

	c='a';
	i=0;
	while ((c != EOF) && (i < segment_size-1))
	{
		c=*(shared_memory+i);
		i++;
	//	printf("i=%d ",i);
		putchar(c);
	}
	putchar('\n');	

//	printf("Text: %s\n",shared_memory);
		
//	do
//	{
//		n=read(fd,string,BUF_SIZE);
//		printf ("N=%d\n",n); 
//		if (n==0) break;
//		snprintf(shared_memory,n,"%s",string);
//	} while (1);

	shmdt(shared_memory);
//	msgctl(id,IPC_RMID,0);
	
	return 0;
}
