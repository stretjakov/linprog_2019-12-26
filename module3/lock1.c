#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char** argv)
{
  int fd,code;

  fd=open(argv[1],O_RDWR|O_APPEND);
  if ( fd == -1) {
    perror("open ");
    exit(EXIT_FAILURE);
  }
  printf("open\n");

  code=flock(fd,LOCK_EX);
  if (code == -1) {
    perror("flock");
    exit(EXIT_FAILURE);
    }
 printf("Мы заблокировали файл %s\n",argv[1]);
 sleep(20);
 write(fd,"Привет\n",strlen("Привет\n"));
 flock(fd,LOCK_UN);
 close(fd);

 exit(EXIT_SUCCESS);
}
