#include <stdio.h>
#include <pthread.h>
#include <math.h>
#define MAX 100

struct pi_params
{
	double xs;
	double xe;
	double h;
};

pthread_mutex_t work_mutex;

double result=0.0;

void* pi (void* parametrs)
{
	double x, sum=0.0;
	struct pi_params* p = (struct pi_params*) parametrs;
	int i;

	for ( x=p->xs; x < p->xe; x+=p->h)
		{
		sum=sum+sqrt(1-x*x); 
		}
	pthread_mutex_lock(&work_mutex);	
	result+=sum;
	pthread_mutex_unlock(&work_mutex);
	return 0;
}

int main(int ac, char **av)
{
	pthread_t th_id[MAX];
	struct pi_params th_arg[MAX];
	int num, i, num_th, res;
	double len, xs, h,sum=0.;
	res = pthread_mutex_init(&work_mutex, NULL);	
	
	num=atoi(av[1]);
	len=(double)1/(double)num;
	
	num_th=atoi(av[2]);
	h=len/(double)num_th;
	
	for (i=1, xs=0.; i <=num; i++,xs+=len )
		{
		(th_arg[i-1].xs)=xs;
		th_arg[i-1].xe=xs+len;
		th_arg[i-1].h=h;
		pthread_create (&th_id[i-1], NULL, &pi, &th_arg[i-1]);
		}
	
	
	for (i=1; i<=num; i++)
		pthread_join (th_id[i-1], NULL);
	

	result*=(h*4.);
	printf ("PI=%lf\n", result);
	
	return 0;
}

