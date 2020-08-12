#include <errno.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
  int status;
  // if missing argument
    if(argc==1)
        printf("please enter the process id\n");
    // if argument exists
    if(argc>=2)
    {
      // call kill on the input.
      status = kill(atoi(argv[1]), 0);
      // if got warning message
      if (status != 0){
        // no permission warning
        if (errno == EPERM) {
           printf("Process %d exists but we have no permission.\n", atoi(argv[1]));
        }
        // if process does not exist
        else if (errno == ESRCH) {
          printf("Process %d does not exist\n", atoi(argv[1]));
        }
        // if process exists
      } else {
        printf("Process %d exists.\n", atoi(argv[1]));
      }
    }
    return 0;
}
