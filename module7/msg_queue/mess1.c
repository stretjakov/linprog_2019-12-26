#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define BUF_SIZE 1024
#define SIZE 1048576

struct amsbuf
{
	long type;
	char text[BUF_SIZE+2];
};

int main (int argc, char* argv[])
{
	int fd,i=0,n,m=0,size=0,err,id;
	char string[BUF_SIZE+10];
	struct amsbuf msg;
	key_t key1;

	msg.type=10;
	
	fd=open(argv[1],O_RDONLY);
	if (fd == -1)
       	{
	       perror("open file %s\n",argv[1]);
	       abort();
	}
	
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
		n=read(fd,msg.text,BUF_SIZE);
		if (n==0) break;
		msgsnd(id,&msg,n,0);
	} while (1);
//	msgctl(id,IPC_RMID,0);
	
	return 0;
}
