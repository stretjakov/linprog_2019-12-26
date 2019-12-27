#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
  pid_t pid;
  int status;
  int fd;
  char buf[50];
  static int a=1;
// Проверить, почему не отработал O_CLOEXEC
  fd=open("/etc/passwd",O_RDONLY|O_CLOEXEC);



  pid=fork();
  switch (pid) {
    case -1: perror("fork"); exit(EXIT_FAILURE);
    case 0: sleep(5);
            printf("Я родился. Мой pid=%ld, Мой родитель %ld a=%d\n", getpid(),getppid(),a);
            read(fd,buf,20);
            write(1,buf,20);
            printf("\n");
            close(fd);
            a=15;
            execlp("/bin/ls","ls","-ld","/tmp",0);
//            system("ls -ld /tmp");
            printf("Я вернулся\n");
            break;
    default:
              a=10;
              printf("Я %ld породил %ld a=%d\n",getpid(),pid,a);
              wait(&status);
              printf("Мой потомок помер со статусом %d\n",status );
              read(fd,buf,20);
              write(1,buf,20);
              printf("\na=%d\n",a);
              break;
  }
  close(fd);
  exit (EXIT_SUCCESS);
}
