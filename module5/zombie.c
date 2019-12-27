//потомок завершает работу до того, как родитель делает wait
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char const *argv[]) {
  pid_t pid;
  int status;

  pid=fork();
  switch (pid) {
    case -1: perror("fork"); exit(EXIT_FAILURE);
    case 0: exit(EXIT_SUCCESS);
    default:  sleep(20);
              wait(&status);
              printf("Мой потомок помер со статусом %d\n",status );
              break;
  }
  exit (EXIT_SUCCESS);
}
