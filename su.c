#include "types.h"
#include "user.h"
#include "syscall.h"
#include "fcntl.h"
#include "passwork.h"
#define MAXLEN 20
int
CheckUser( int fd,char *user , char *passwd, char *ID)
{
    char allWord[128];
    char Auser[MAXLEN];
    char AID[MAXLEN];
    char Apassword[MAXLEN];

    int num = 0;
    if(user[strlen(user)-1]  == '\n'){
  	    user[strlen(user)-1]  = '\0';	
    }

    while((num = read(fd, allWord, sizeof(allWord))) > 0){
        for(int i =0;i<num;i++)
        {
            i = readpasswdfile(allWord,Auser,Apassword,AID,num,i);
            if(i == -1)break;
            
            if(!strcmp(user,Auser)){
                strcpy(passwd,Apassword);
                strcpy(ID,AID);
                return 1;
            }
        }
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    int fd,writefd,flag = 0;
    char *userpasswd,*user = "";
    char password[MAXLEN],ID[MAXLEN];
    if((writefd = open("/nowuserid", O_WRONLY)) < 0){
        printf(1,"su: can't open nowuserid\n");
        exit();
    } 
    if((fd = open("/userpasswd", O_RDONLY)) < 0){
        close(writefd);
        printf(1,"su: can't open Userpassword\n");
        exit();
    }
    if(argc == 1)
    {
        flag = CheckUser(fd,"root",password,ID);
        strcpy(user,"root");
    }
    else if(argc == 2)
    {
        flag = CheckUser(fd, argv[1],password,ID);
        strcpy(user,argv[1]);
    }
    else
    {
        close(fd);
        close(writefd);
        printf(2,"su: error\n");
        exit();
    }

    if(flag == 1)
    {
        printf(1,"Password: ");
        userpasswd = gets("password", MAXLEN);

        if(userpasswd[strlen(userpasswd)-1]  == '\n'){
  	        userpasswd[strlen(userpasswd)-1]  = '\0';	
        }
        if(!strcmp(userpasswd,password)){
            if(write(writefd,ID,sizeof(ID)) <= 0)
            {
                printf(1,"su: write file error\n");
                close(fd);
                close(writefd);
                exit();
            }
            printf(2,"Welcome\n",user);
        }
         if(strcmp(userpasswd,password)!=0){
             printf(2,"su: user password error\n");
         }
    }
    else
    {
        printf(2,"su: no such user\n");
        close(fd);
        close(writefd);
        exit();
    }
    close(fd);
    close(writefd);
    exit();
}