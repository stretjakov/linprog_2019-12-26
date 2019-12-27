#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define BUF_SIZE 1024
#define SIZE 1048576

int main (int argc, char* argv[])
{
	int fd,i=0,n,m=0,size=0,err,id, id_sem, sem_val;
	char string[BUF_SIZE+10];
	char *shared_memory, *p;
	union semun 
	{
		int val;
		struct semid_ds buf[1];
		unsigned short int array[1];
		struct seminfo __buf[1];
	} options;
	struct sembuf sem;
		
	key_t key1;
	key1=ftok("/home/user1",'s');
	
		
	fd=open(argv[1],O_RDONLY);
	if (fd == -1)
       	{
	       perror("open file %s\n",argv[1]);
	       abort();
	}
	
	id=shmget(key1,BUF_SIZE, IPC_CREAT | 0666);
	id_sem=semget(key1,1,IPC_CREAT | 0666);
	
	options.val=5;
	semctl(id_sem,0,SETVAL,options);
	sem_val=semctl(id_sem,0,GETVAL,0);
	printf("sem_val=%d\n",sem_val);

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
		while (1)
		{
			sem_val=semctl(id_sem,0,GETVAL,0);
			if (sem_val == 3 || sem_val == 5)
			{
			       	snprintf(shared_memory,n,"%s",string); 
				options.val=2;
				semctl(id_sem,0,SETVAL,options);
				break;
			}
		}
		
		
	} while (1);
	shmdt(shared_memory);
	options.val=4;
	semctl(id_sem,0,SETVAL,options);
//	msgctl(id,IPC_RMID,0);
	
	return 0;
}
