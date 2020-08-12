#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


struct stat sb2;
// https://linux.die.net/man/3/nftw
static int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{

    // https://stackoverflow.com/questions/3984948/how-to-figure-out-if-a-file-is-a-link
    // https://linux.die.net/man/2/stat
    // get also inode data and sl info
    lstat(fpath, &sb2);
    // because in task was asked no printing soft link.
    if (!S_ISLNK(sb2.st_mode))
    {
      printf("%-3s I-node: %-7ld %-10s FOR MORE INFO:  %2d %7jd   %-20s %-3d \n",
          (tflag == FTW_D) ?   "D"   : (tflag == FTW_DNR) ? "DNR" :
          (tflag == FTW_DP) ?  "DP"  : (tflag == FTW_F) ?   "F" :
          (tflag == FTW_NS) ?  "NS"  : (tflag == FTW_SL) ?  "SL" :
          (tflag == FTW_SLN) ? "SLN" : "???", (long) sb2.st_ino, fpath + ftwbuf->base, // for task
          ftwbuf->level, (intmax_t) sb->st_size, fpath, ftwbuf->base); // for understanding
    }
    return 0;           /* To tell nftw() to continue */
}

int main(int argc, char *argv[])
{
  int flags = 0;
  // get dir to view
  if (argc > 2 && strchr(argv[2], 'd') != NULL)
       flags |= FTW_DEPTH;
   if (argc > 2 && strchr(argv[2], 'p') != NULL)
       flags |= FTW_PHYS;

  if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags) == -1) {
       perror("nftw");
       exit(EXIT_FAILURE);
   }
   exit(EXIT_SUCCESS);

}
