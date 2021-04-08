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
    //child
    close(pipefd[0]);
    const char *msg = "I am child ......!\n";
    int count = 0;
    while(1){
      write(pipefd[1],msg,strlen(msg));
      printf("%d\n",count++);
      if(count == 5){
        close(pipefd[1]);
        break;
      }
    }
    exit(2);
  }
  else{
    //parent
    close(pipefd[1]);
    char buffer[64];
    while(1){
      ssize_t s = read(pipefd[0],buffer,sizeof(buffer)-1);// 是因为文件里面的内容读出来，想要以字符串的形式显示
        if(s > 0){
          //说明读取成功
          buffer[s] = '\0';
          printf("father get message : %s\n",buffer);
          sleep(1);
        }
        printf("father exit return : %d\n",s);
    }
 }
  return 0;
}
