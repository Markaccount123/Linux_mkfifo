#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"common.h"
#include<unistd.h>
#include<string.h>
int main()
{
  //client依旧要保留着这个key值
  //第一步首先给操作系统一个标识ftok
  key_t k = ftok(PATHNAME,PROJ_ID);

  //成功则会返回一个非负整数，失败则会返回-1
  int shmid = shmget(k,SIZE,0);
  
  if(shmid < 0)
  {
    perror("shmget error\n");
    return 1;
  }

  char *str = shmat(shmid,NULL,0);

  const char *msg = "i am process A";

  memcpy(str,msg,strlen(msg)+1);

  shmdt(str);
  sleep(5);
  return 0;
}
