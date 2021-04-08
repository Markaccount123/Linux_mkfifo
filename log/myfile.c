#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
void handler(int signo)
{
  printf("catch a signal : %d\n",signo);
}
int main(int argc,char *argv[])
{
  printf("begin...\n");

  int i = 1/0;

  printf("end...\n");

  return 0;
}
