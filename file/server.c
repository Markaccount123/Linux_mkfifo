#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define FIFO_FILE "./fifo"
int main()
{
  //对于server来说应该首先创建管道
  umask(0);
  if(-1 == mkfifo(FIFO_FILE,0666))
  {
    perror("mkfifo error\n");
    return 1;
  }

  int fd = open(FIFO_FILE,O_RDONLY);
  if(fd >= 0)
  {
    char buffer[64];
    while(1)
    {
      ssize_t s = read(fd,buffer,sizeof(buffer)-1);
      if(s > 0)
      {
        buffer[s] = '\0';
        printf("%s",buffer);
      }
      else if(s == 0)
      {
        //为0的时候说明，读取文件结束
        printf("write quit me too\n");
        break;
      }
      else 
      {
        //读失败了
        perror("read");
        break;
      }
    }

  }
}
