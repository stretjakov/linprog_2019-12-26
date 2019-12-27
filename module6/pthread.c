#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define MAX_TH 100

void* char_print(void *);
pthread_mutex_t mt;
int sum=0;

int main(int argc, char **argv)
{
  pthread_t pth_id[MAX_TH];
  int code,i,num;
  char ch[MAX_TH], ch1;
  int n[MAX_TH];

  pthread_mutex_init(&mt,NULL);

  num=atoi(argv[1]);
//  printf("num=%d %c\n",num,ch++);

  ch1='a';
  for (i=0; i < num; i++)
    {
      ch[i]=ch1;
      code=pthread_create(&pth_id[i],NULL,&char_print, (void *)&ch[i]);
//    if (code != 0) perror("pthread_create");
      ch1++;
    }

  for (i=0; i < num; i++)
      {
        code=pthread_join(pth_id[i],(void *)&n[i]);
//        if (code != 0) perror("pthread_join");
      printf("\npth=%c n=%d\n",ch[i],n[i]);
      }
      printf("sum=%d\n",sum);
      pthread_mutex_destroy(&mt);
  exit(EXIT_SUCCESS) ;
}

void *char_print(void* ch)
{
  char* ch1=(char *) ch;
  long r;
  int i, num,code;

  r=random();
  num=(int)(r%100000L);

  for (i=1; i<=num ; i++)
//    write(1,ch1,1);
      fputc(*ch1,stdout);
//  printf("\nиз потока ch=%c num=%d\n",*ch1,num);
  code=pthread_mutex_lock(&mt);
//  if (code !=0) fprintf(stderr,"Проблема с мьютексом\n");
  sum=sum+num;
//  printf("\nиз потока ch=%c sum=%d\n",*ch1,sum);
  pthread_mutex_unlock(&mt);
return num;
}
