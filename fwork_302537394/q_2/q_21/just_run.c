#include <stdio.h>
#include <sys/types.h>
int main(int argc,char* argv[])
{
  // print process id
  pid_t pid = getpid();
  printf("pid: %d\n", pid);
  while(1){
    sleep(1);
  };
  return 0;
}
