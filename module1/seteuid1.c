// Запуск процесса от имени другого пользователя
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main (void)
{
  uid_t euid=0;
  int code;

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
