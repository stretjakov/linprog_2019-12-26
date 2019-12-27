// ./fork_stdio3
// ./fork_stdio3 > fork_stdio.out
// эот вариант правильно работает

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char const *argv[]) {

  int code;

  printf("hello1\n");
  fflush(NULL);

  code=fork();
  switch (code) {
    case 0: printf("hello2\n"); exit(EXIT_SUCCESS);
    default: printf("hello2\n"); exit(EXIT_SUCCESS);
  }

}
