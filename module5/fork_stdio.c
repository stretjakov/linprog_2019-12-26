#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char const *argv[]) {

  printf("hello1\n");
//  fflush(NULL); /* так будет работать правильно */
  fork();
  printf("hello2\n");

  exit(EXIT_SUCCESS);
}
