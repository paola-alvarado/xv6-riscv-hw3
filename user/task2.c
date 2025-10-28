#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid;

  pid = fork();
  if(pid == 0){
    setpriority(40);
    for(int i=0;i<5;i++){
      printf("Child A ran (priority=%d, ticks=%d)\n", getpriority(), uptime());
      sleep(1);
    }
    exit(0);
  }

  pid = fork();
  if(pid == 0){
    setpriority(39);
    for(int i=0;i<5;i++){
      printf("Child B ran (priority=%d, ticks=%d)\n", getpriority(), uptime());
      sleep(1);
    }
    exit(0);
  }

  pid = fork();
  if(pid == 0){
    setpriority(40);
    for(int i=0;i<5;i++){
      printf("Child C ran (priority=%d, ticks=%d)\n", getpriority(), uptime());
      sleep(1);
    }
    exit(0);
  }

  wait(0); wait(0); wait(0);
  exit(0);
}