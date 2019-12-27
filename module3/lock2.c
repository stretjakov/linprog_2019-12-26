// Чтобы блокировка файла стала mandatory нужно
// mount -o remount,mand точка_монтирования
// chmod g-x,g+s имя_файла
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
  struct flock lck;

  fd=open(argv[1],O_RDWR|O_APPEND);
  if ( fd == -1) {
    perror("open ");
    exit(EXIT_FAILURE);
  }
  printf("open\n");

  lck.l_type = F_WRLCK;
  lck.l_start = 0;
  lck.l_len = 0;
  lck.l_whence = SEEK_SET;

  code=fcntl(fd,F_SETLKW,&lck);
  if (code == -1) {
    perror("fcntl");
    exit(EXIT_FAILURE);
    }
 printf("Мы заблокировали файл %s\n",argv[1]);
 sleep(20);
 write(fd,"Привет\n",strlen("Привет\n"));

 lck.l_type = F_UNLCK;
 lck.l_start = 0;
 lck.l_len = 0;
 lck.l_whence = SEEK_SET;
 code=fcntl(fd,F_SETLKW,&lck);

 close(fd);

 exit(EXIT_SUCCESS);
}
