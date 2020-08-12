// imports
#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>
#include <linux/sched.h>
#include <sys/types.h>
// for SCHED_DEADLINE
struct sched_attr {
    uint32_t size;

    uint32_t sched_policy;
    uint64_t sched_flags;

    /* SCHED_NORMAL, SCHED_BATCH */
    int32_t sched_nice;

    /* SCHED_FIFO, SCHED_RR */
    uint32_t sched_priority;

    /* SCHED_DEADLINE (nsec) */
    uint64_t sched_runtime;
    uint64_t sched_deadline;
    uint64_t sched_period;
};
// for SCHED_DEADLINE
int sched_setattr(pid_t pid, const struct sched_attr *attr, unsigned int flags)
{
   return syscall(__NR_sched_setattr, pid, attr, flags);
}
 int main(int argc, char* argv[]) {
   // print process id
   pid_t pid = getpid();
   printf("pid: %d\n", pid);
   // change priority on the struct
   const struct sched_param attr_param = {
       .sched_priority = atoi(argv[2])
   };
   // http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fs%2Fsched_setscheduler.html
   // change sched policy
   if (atoi(argv[1]) != 6)
   {
     sched_setscheduler(0, atoi(argv[1]), &attr_param);
   } else
   {
     struct sched_attr attr = {
        .size = sizeof(attr),
        .sched_priority = atoi(argv[2]),
        .sched_policy = SCHED_DEADLINE,
        .sched_runtime = 30000000,
        .sched_period = 100000000,
        .sched_deadline = 100000000
    };

    pid_t tid = syscall(SYS_gettid);

    if (sched_setattr(tid, &attr, 0))
        perror("sched_setattr()");

   }
   // keep thread alive
   while(1){
     sleep(1);
   };
   return 0;
 }
