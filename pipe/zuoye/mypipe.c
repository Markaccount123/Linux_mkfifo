#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main()
{
  int pipefd[2] = {0};

  pipe(pipefd);

  pid_t id = fork();
  if(id < 0){
    perror("fork error\n");
  }
  else if(id == 0){
    //child read 
    char buffer[64];
    close(pipefd[1]);
    while(1){
      ssize_t s = read(pipefd[0],buffer,sizeof(buffer)-1);
      if(s > 0){
        buffer[s] = '\0';
        printf("child receive : %s\n",buffer);
      }
      else if(s == 0){
        printf("read quit write too\n");
        break;
      }
      else{
        perror("read error\n");
        break;
      }
    }
  }
  else{
    //parent write
    close(pipefd[0]);
    const char *msg = "i am father\n";
    while(1){
      write(pipefd[1],msg,strlen(msg));
      sleep(1);
    }
  }
  return 0;
}
