#include <errno.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
  int status;
  // if missing argument
    if(argc<4)
        printf("please enter the process id...\n");
    // if argument exists
    if(argc>=4)
    {
      // call kill on the input.
      for (int i=0;i<atoi(argv[3]);++i)
      {
        status = kill(atoi(argv[1]), atoi(argv[2]));
      }
    }
    return 0;
}
