#include <stdio.h>
#include <assert.h>

int main ()
{
  double number;

  printf("Введите число: ");
  scanf("%lf", &number);
  assert(number != 0);
  printf("Обратное значение числа равно %lf \n",1.0/number);
  return 0;
}
