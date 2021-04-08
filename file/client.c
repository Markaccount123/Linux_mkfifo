#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define FIFO_FILE "./fifo"
int main()
{

  int fd = open(FIFO_FILE,O_WRONLY);
  if(fd >= 0)
  {
    const char *msg = "i am process A\n";
    while(1)
    {
      write(fd,msg,strlen(msg));
      sleep(3);
    }
  }
  return 0;
}
