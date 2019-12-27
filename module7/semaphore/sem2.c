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
#include <sys/sem.h>


#define SIZE 1048576

int main (int argc, char* argv[])
{
	int fd,i=0,n,m=0,size=0,err,id;
	char *shared_memory, c;
	struct shmid_ds shmbuffer;
	int segment_size;
	key_t key1;
	int id_sem, sem_val;
	union semun 
	{
		int val;
		struct semid_ds buf[1];
		unsigned short int array[1];
		struct seminfo __buf[1];
	} options;
	struct sembuf sem;
	
	key1=ftok("/home/user1",'s');
	
	id=shmget(key1,0, IPC_CREAT | 0440);
		
	if (id == -1)
	{
		perror("Error");
		abort();
	}
	
	id_sem=semget(key1,0,IPC_CREAT | 0666);
	
	shared_memory=(char*) shmat(id,0,0);
	shmctl (id,IPC_STAT,&shmbuffer);
	segment_size=shmbuffer.shm_segsz;
	
	//printf("Segment size=%d\n",segment_size);
	
while (1)
{
sem_val=semctl(id_sem,0,GETVAL,0);
if (sem_val == 2 )
	{
	c='a';
	i=0;
	while ((c != EOF) && (i < segment_size-1))
		{
		c=*(shared_memory+i);
		i++;
	//	printf("i=%d ",i);
		putchar(c);
		}
	options.val=3;
	semctl(id_sem,0,SETVAL,options);
	} else if (sem_val == 4) break;
}
	putchar('\n');	


	shmdt(shared_memory);
	
	return 0;
}


