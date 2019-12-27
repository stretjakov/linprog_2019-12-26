/*
Когда закрывается открытый на запись файл, выводится сообщение на экран
и подсчитывается md5 сумма
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))
#define STATE IN_CLOSE_WRITE


int main(int argc, char **argv) {
    int fd,wd,i;
    ssize_t num;
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    struct inotify_event* event;
    char *p;
    char *actions[]={"IN_ACCESS","IN_MODIFY","IN_ATTRIB","IN_CLOSE_WRITE",
                       "IN_CLOSE_NOWRITE","IN_OPEN","IN_MOVED_FROM",
                       "IN_MOVED_TO","IN_CREATE","IN_DELETE",
                       "IN_DELETE_SELF","IN_MOVE_SELF"};
    char command[1024];

    strcpy(command,"md5sum -b ");
    strcat(command,argv[1]);
    printf("%s\n", command);

/*  инициализируем сборщик событий*/
    fd = inotify_init();
    if (fd == -1) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }
    printf("inotify инициализирован\n");

//  мониторим все события, происходящие с файлом,
//  имя которого передано через командную строку
    printf("Начинаем мониторинг файла %s\n",argv[1]);
    wd = inotify_add_watch(fd, argv[1], STATE);
    if (wd == -1) {
          perror("inotify_add_watch");
          exit(EXIT_FAILURE);
   /* если выводится сообщение: inotify_add_watch: No space left on device
   то можно выполнить команду от имени root
   echo fs.inotify.max_user_watches=65536 | tee -a /etc/sysctl.conf && sysctl -p
   */
    }

    /* Читаем поступающие события */
    for(;;) {
        num = read(fd, buf, BUF_LEN);
        if (num == 0) {
            printf("Код возврата read() равен 0\n");
            exit(EXIT_FAILURE);
            }
        for (p = buf; p < buf + num; ) {
            event = (struct inotify_event *) p;
            if(event->mask & STATE) {
              printf("С файлом %s произошло событие %s с кодом %d\n",
                argv[1], actions[(int)(log2(event->mask))], event->mask);
              system(command);
            }
            p += sizeof(struct inotify_event) + event->len;
            }
        }

    exit(EXIT_SUCCESS);
}
