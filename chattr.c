#include "types.h"
#include "user.h"
#include "syscall.h"
int
main(int argc, char *argv[])
{
    int flag = 0;
    int attrmode = 0;
    if(argc != 3)
    {
        printf(2,"chattr: You enter wrong input \nHelp: Please enter the fliename and mode\n");
        exit();
    }
    if(!strcmp( argv[1],"-i"))
    {
        attrmode = 0;
    }
    else if(!strcmp( argv[1],"+i"))
    {
        attrmode = 1;
    }
    else 
    {
        printf(2,"chattr: You enter wrong attrmode %s\n",argv[1]);
        exit();
    }

    if((flag = chattr(argv[2],attrmode))>=0){
        printf(2,"chattr flag = %d\n",flag);
    }
    else if(flag == -1)
    {
        printf(2,"chattr: You enter wrong input \nHelp: Please enter the fliename and mode\n");
    }
    else if(flag == -2)
    {
        printf(2,"chattr: Your input file %s is not exist\n",argv[2]);
    }
    else if(flag == -3)
    {
        printf(2,"chattr: You input mode not in the range\n");
    }
    else if(flag == -4)
    {
        printf(2,"chattr: premission deny\n");
    }
    exit();
}