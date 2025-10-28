// user/pexecx.c
#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

// Usage: pexecx <priority> <cmd> [args...]
int
main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("Usage: pexecx <priority> <cmd> [args...]\n");
    exit(1);
  }

  int prio = atoi(argv[1]);
  setpriority(prio);                 // parent sets base priority

  // build argv for exec from argv[2..]
  char *cmdv[MAXARG];
  int i;
  for (i = 2; i < argc && (i - 2) < MAXARG - 1; i++)
    cmdv[i - 2] = argv[i];
  cmdv[i - 2] = 0;

  int p[2];
  if (pipe(p) < 0) { printf("pipe failed\n"); exit(1); }

  uint t_arrival = uptime();
  int pid = fork();
  if (pid < 0) { printf("fork failed\n"); exit(1); }

  if (pid == 0) {
    close(p[0]);
    setpriority(prio);               // ensure child priority
    uint t_first = uptime();         // first timestamp from child
    write(p[1], &t_first, sizeof(t_first));
    close(p[1]);
    exec(cmdv[0], cmdv);
    printf("exec %s failed\n", cmdv[0]);
    exit(1);
  }

  close(p[1]);
  uint t_first = 0;
  if (read(p[0], &t_first, sizeof(t_first)) != sizeof(t_first)) {
    printf("failed to read child start time\n");
    close(p[0]);
    wait(0);
    exit(1);
  }
  close(p[0]);

  wait(0);
  uint t_end = uptime();

  int resp = (int)(t_first - t_arrival);  // response time
  int turn = (int)(t_end   - t_arrival);  // turnaround time

  printf("prio=%d  resp=%d ticks  turn=%d ticks  cmd=", prio, resp, turn);
  for (i = 2; argv[i]; i++) printf("%s%s", (i==2?"":" "), argv[i]);
  printf("\n");
  exit(0);
}