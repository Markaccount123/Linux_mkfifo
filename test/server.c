#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"common.h"
#include<unistd.h>
#include<string.h>

int main()
{
  //第一步首先给操作系统一个标识ftok
  key_t k = ftok(PATHNAME,PROJ_ID);

  //成功则会返回一个非负整数，失败则会返回-1
  int shmid = shmget(k,SIZE,IPC_CREAT | IPC_EXCL|0666);
  
  if(shmid < 0)
  {
    perror("shmget error\n");
    return 1;
  }

  char *str = shmat(shmid,NULL,0);

  while(1)
  {
    sleep(1);
    printf("%s\n",str);
  }
  shmdt(str);

  shmctl(shmid,IPC_RMID,NULL);  //既不查询，也不设置，所以设置为NULL
  return 0;
}
