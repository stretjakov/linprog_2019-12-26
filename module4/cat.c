#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int fd;
  void *p;
  struct stat sb;

  fd=open(argv[1],O_RDONLY);
  fstat(fd, &sb);
  p=mmap(NULL, sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
  if (p == NULL) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  write(1,p,sb.st_size);

  exit(EXIT_SUCCESS);
}
