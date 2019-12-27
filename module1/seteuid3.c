// Запуск процесса от имени другого пользователя
// Использование опций
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <locale.h>

int main (int argc, char **argv)
{
  uid_t euid;
  int code;
  char opt;

  setlocale(LC_ALL,"");
  while ((opt=getopt(argc,argv,"rps:")) != EOF)
    switch (opt)
    {
      case 's': euid=(uid_t)atoi(optarg);
                code = seteuid(euid);
                if (code == -1 )
                {
                  if ( errno == EINVAL )
                  perror("Невалидный UID.\nseteuid");
                  if ( errno == EPERM )
                  perror ("У Вас нет прав запускать процесс от чужого имени.\nseteuid");
                }
                printf("EUID=%d\n", geteuid());
                break;
      case 'r': printf("RUID=%d\n", getuid() ); break;
      case 'p': printf("PID=%d\n", getpid()); break;
      default: fprintf(stderr,"Использование: %s -rps UID_пользователя\n", argv[0]); break;
    }

/* если нужно делать разбор следующих за опциями аргументов */
  for (int i=optind; i< argc; i++)
    printf ("%d %s\n", i, argv[i]);

  return 0;
}
