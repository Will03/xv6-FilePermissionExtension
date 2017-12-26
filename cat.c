#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
fcat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i,flag;

  if(argc <= 1){
    cat(0);
    exit();
  }
  for(i = 1; i < argc; i++){
    if((flag = cat(argv[i]))<0){
      if(flag == -3)
        printf(2, "cat: premission deny\n");
      else if(flag == -2)
        printf(2, "cat: open file error\n");
      else if(flag == -1)
        printf(2, "cat: input error\n");
      exit();
    }
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    fcat(fd);
    close(fd);
  }
  exit();
}
