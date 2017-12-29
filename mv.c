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


  int flag = mv(argv[1],argv[2]);
  if(flag <0){ 
    if(flag == -3){
      printf(1, "mv: permission deny.\n");
    }
    else if(flag == -2){
      printf(1, "mv: error to open the file.\n");
    }
    else if(flag == -1){
      printf(1, "mv: error to open the file.\n");
    }
    exit();
  }
  else{
    printf(1,"good\n");
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
  else if(distination == -2){
    printf(1, "mv: permission deny.\n");
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
