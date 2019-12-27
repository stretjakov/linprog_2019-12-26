// ./fork_stdio2
// ./fork_stdio2 > fork_stdio.out

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char const *argv[]) {

  int code;

  printf("hello1\n");

  code=fork();
  switch (code) {
    case 0: printf("hello2\n"); _exit(EXIT_SUCCESS);
    default: printf("hello2\n"); exit(EXIT_SUCCESS);
  }

}
