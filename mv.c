#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

#define BUFFER_SIZE 256

int
main(int argc, char *argv[]){
  if(argc != 3){
    printf(1, "Command Error, please check the argument.\n");
    exit();
  }

  int source = open(argv[1], 0);
  if(source == -1){
    printf(1, "Source file can not open.\n");
    exit();
  }
  
  int distination = open(argv[2], O_WRONLY | O_CREATE);
  if(distination == -1){
    printf(1, "Distination file can not write, Please Contact the root.\n");
    exit();
  }
  
  char buffer[BUFFER_SIZE];
  int length = 0;
  while((length = read(source, buffer, BUFFER_SIZE)) > 0)
    write(distination, buffer, length);

  close(source);
  close(distination);

  if(unlink(argv[1]) < 0)
    printf(1, "Can not Delete Source file.\n");
  exit();
}
