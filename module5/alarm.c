#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/mman.h>

sig_atomic_t flag_atom=0;

void  alarm_handler(int signal_number)
{
flag_atom=1;
}


int main ( int argc, char **argv)
{
struct itimerval time0;
struct sigaction sa;

memset(&sa,0,sizeof(sa));
memset(&time0,0,sizeof(time0));

time0.it_value.tv_sec=atol(argv[1]);
time0.it_interval.tv_sec=atol(argv[2]);

setitimer(ITIMER_REAL,&time0, NULL);

sa.sa_handler= &alarm_handler;
sigaction(SIGALRM, &sa, NULL);

for (;;)
  { 
  write(1,".",1);
  if ( flag_atom==1) { write(2,"Alarm\n", 6); flag_atom=0;}
  }


return 0;
}


 
