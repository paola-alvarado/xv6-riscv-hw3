#include "kernel/types.h"
#include "user/user.h"

static void hog(void){ volatile int x=0; for(;;) x++; }

int main(void){
  setpriority(49);
  int hp = fork();
  if(hp==0){ hog(); exit(0); }

  setpriority(0);
  int start = uptime();
  int low = fork();
  if(low==0){
    int t = uptime();
    printf("[LOW] ran at tick %d (wait=%d)\n", t, t-start);
    exit(0);
  }

  wait(0);           // wait for low child to get CPU via aging
  kill(hp); wait(0); // cleanup
  exit(0);
}