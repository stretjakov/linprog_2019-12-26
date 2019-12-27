#include <stdio.h>
#include <string.h>

extern char** environ;

char *get_environ(char *env_name)
{
  int i=0;

  while ( environ[i] != NULL)
  {
    if (strncmp(environ[i],env_name,strlen(env_name)) == 0)
       {
         printf("environ %s\n", environ[i]);
         break;
       }
    i++;
  }
  return (environ[i]);
}
