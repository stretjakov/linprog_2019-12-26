#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mcheck.h>
#include <locale.h>

int main (void)
{
  char *buf1, *buf2;
  int NUM1=10, NUM2=20;

//  setlocale(LC_ALL,"");
  mtrace();
  if (mcheck(NULL) != 0) {
      fprintf(stderr, "mcheck() failed\n");
      exit(EXIT_FAILURE);
      }

  printf("0 Начало памяти=%p\n",sbrk(0));
  buf1=(char *)malloc(NUM1*sizeof(*buf1));
  if (buf1 == NULL) {perror("buf1 calloc"); exit(EXIT_FAILURE);}
  printf("1_1 Начало памяти=%p\n",buf1);

  buf2=(char *)malloc(NUM2*sizeof(*buf2));
  if (buf2 == NULL) {perror("buf2 calloc"); exit(EXIT_FAILURE);}
  printf("2_1 Начало памяти=%p\n",buf2);

  strcpy(buf2,"ПокаПока");
  strcpy(buf1,"ПриветПриветПриветПриветПриветПриветПриветПриветПриветПривет");

  printf("buf1 Из памяти %s\n",buf1);
  printf("buf2 Из памяти %s\n",buf2);

  free((void *)buf1);
  printf("1_2 Начало памяти=%p\n",sbrk(0));
  free((void *)buf2);
  printf("2_2 Начало памяти=%p\n",sbrk(0));

  exit(EXIT_SUCCESS);
}
