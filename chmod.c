#include "types.h"
#include "user.h"
#include "syscall.h"
int
main(int argc, char *argv[])
{
    int flag = 0;
    if(argc != 3)
    {
        printf(2,"chmod: You enter wrong input \nHelp: Please enter the fliename and mode\n");
        exit();
    }
    if((flag = chmod(argv[2],atoi(argv[1])))>100){
    printf(2,"chmod flag = %d\n",flag);
    }
    else if(flag == -1)
    {
        printf(2,"chmod: You enter wrong input \nHelp: Please enter the fliename and mode\n");
    }
    else if(flag == -2)
    {
        printf(2,"chmod: Your input file %s is not exist\n",argv[2]);
    }
    else if(flag == -3)
    {
        printf(2,"chmod: You input mode not in the range\n");
    }
    else if(flag == -4)
    {
        printf(2,"chattr: premission deny\n");
    }
    exit();
}