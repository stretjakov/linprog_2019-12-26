#include <stdio.h>
#include <stdlib.h>

char* get_env(char **, char *);
char* get_environ(char *);

int main(int argc, char **argv, char **env)
{
  if ( argc !=2 )
   {
     fprintf(stderr,"Использование: %s имя_переменной\n", argv[0]);
     exit (EXIT_FAILURE);
   }

   get_env(env,argv[1]);
   get_environ(argv[1]);
   printf("getenv %s=%s\n",argv[1],getenv(argv[1]));

  return 0;
}
