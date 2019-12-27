#include <stdio.h>
#include <string.h>


char *get_env(char **str, char *env_name)
{
  int i=0;

  while ( str[i] != NULL)
  {
    if (strncmp(str[i],env_name,strlen(env_name)) == 0)
       {
         printf("env %s\n", str[i]);
         break;
       }
    i++;
  }
  return (str[i]);
}
