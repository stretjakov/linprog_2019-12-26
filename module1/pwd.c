#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char** environ;

int main(int argc, char **argv, char **env)
{
  int i=0;

  while ( env[i] != NULL)
  {
    if (strncmp(env[i],"PWD=",4) == 0)
      printf("%s\n", env[i]);
    i++;
  }

  i=0;
  while ( environ[i] != NULL)
  {
    if (strncmp(environ[i],"PWD=",4) == 0)
      printf("%s\n", environ[i]);
    i++;
  }

  printf("PWD=%s\n", getenv("PWD"));

return 0;
}
