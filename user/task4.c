#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid_low, pid_high;

  pid_low = fork();
  if(pid_low == 0){
    setpriority(5);   // very low priority
    for(int i = 0; i < 5; i++){
      printf("[LOW] ran at tick %d\n", uptime());
      sleep(50);
    }
    exit(0);
  }

  pid_high = fork();
  if(pid_high == 0){
    setpriority(50);  // high priority
    for(int i = 0; i < 5; i++){
      printf("[HIGH] ran at tick %d\n", uptime());
      sleep(50);
    }
    exit(0);
  }

  wait(0);
  wait(0);
  exit(0);
}