#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#define BUF_SIZE 1024
#define SIZE 1024


struct amsbuf
{
	long type;
	char text[BUF_SIZE+2];
};
	
int main (int argc, char* argv[])
{
	int i=0,n,m=0,size=0,err,id;
	struct amsbuf msg;
	key_t key1;
	
	msg.type=10;

	key1=ftok("/home/user1",'e');
	printf("Key1=%d\n",key1);
	
	id=msgget(key1,IPC_CREAT | 0666);
	
	if (id == -1)
	{
		perror("Error");
		abort();
	}
	do 
	{
		n=msgrcv(id,&msg,BUF_SIZE,10,0);
		//n=msgrcv(id,&msg,BUF_SIZE,10,IPC_NOWAIT);
		//printf("N=%d\n",n);
		
		size=size+n;
		if (size >= SIZE)
		{
		m=m+1;
		printf("Get %d \n",m);
		size=size-SIZE;
		}
	} while ( n >= 0);
	return(0);
}
