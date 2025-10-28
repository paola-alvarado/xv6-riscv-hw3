#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
    struct pstat uproc[NPROC];
    int nprocs;
    int i;
    char *state;
    static char *states[] = {
        [SLEEPING] "sleeping",
        [RUNNABLE] "runnable",
        [RUNNING]  "running ",
        [ZOMBIE]   "zombie  "
    };

    nprocs = getprocs(uproc);
    if (nprocs < 0)
        exit(-1);

    uint now = uptime(); // current time in ticks

    printf("pid\tstate\t\tsize\tppid\tpriority\tage\tname\n");

    for (i = 0; i < nprocs; i++)
    {
        state = states[uproc[i].state];
        int age = (int)(now - uproc[i].readytime);
        if (age < 0)
            age = 0;

        printf("%d\t%s\t%d\t%d\t%d\t\t%d\t%s\n",
               uproc[i].pid,
               state,
               uproc[i].size,
               uproc[i].ppid,
               uproc[i].priority,
               age,
               uproc[i].name);
    }

    exit(0);
}