// Запуск процесса от имени другого пользователя
// Ввод uid от имени, которого запускается процесс, как аргумент
// командной строки.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main (int argc, char **argv)
{
  uid_t euid;
  int code;

  if (argc != 2)
  {
    fprintf(stderr, "Неверное кол-во аргументов\n");
    fprintf(stderr, "Usage: %s uid_пользователя\n", argv[0] );
    return -1;
  }

  euid=(uid_t)atoi(argv[1]);

  code = seteuid(euid);
  if (code == -1 )
  {
    if ( errno == EINVAL )
      perror("Невалидный UID. seteuid");
    if ( errno == EPERM )
      perror ("У Вас нет прав запускать процесс от чужого имени. seteuid");
    exit (EXIT_FAILURE);
  }

  printf("Процесс запущен от имени пользователя с UID=%d\n", geteuid());
  return 0;
}
