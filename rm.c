#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i,flag = 0;

  if(argc < 2){
    printf(2, "Usage: rm files...\n");
    exit();
  }

  for(i = 1; i < argc; i++){
    flag = unlink(argv[i]);
    if(flag<0){
      if(flag ==-2)
        printf(2, "rm: permission deny\n");
      else if(flag !=-2)
        printf(2, "rm: %s failed to delete\n", argv[i]);

      break;
    }
    else 
      printf(2,"rm sucess\n");
  }
  exit();
}


