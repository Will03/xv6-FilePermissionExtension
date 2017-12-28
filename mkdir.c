#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i,flag = 0;

  if(argc < 2){
    printf(2, "Usage: mkdir files...\n");
    exit();
  }

  for(i = 1; i < argc; i++){
    if((flag = (mkdir(argv[i]))) < 0){
      if(flag == -2)
        printf(2, "mkdir: %s failed to create: permission deny\n", argv[i]);
      else
        printf(2, "mkdir: %s failed to create %d\n", argv[i],flag);
      break;
    }
  }

  exit();
}
