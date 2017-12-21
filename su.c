#include "types.h"
#include "user.h"
#include "syscall.h"
#include "fcntl.h"
#define MAXLEN 20
int
CheckUser( int fd,char *user , char *passwd, char *ID)
{
    char allWord[128];
    char Auser[MAXLEN];
    char AID[MAXLEN];
    char Apassword[MAXLEN];

    int num = 0,now = 0;
    if(user[strlen(user)-1]  == '\n'){
  	    user[strlen(user)-1]  = '\0';	
    }

    while((num = read(fd, allWord, sizeof(allWord))) > 0){
        for(int i =0;i<num;i++)
        {
            now =0;
            for(;allWord[i]!=';'||i == num;i++,now++){
                Auser[now] = allWord[i];
            }
            i++;
            Auser[now] = '\0';
            if(i>=num){
                printf(1,"Login:AccountFile have error\n");
                break;
            }
            
            now =0;
            for(;allWord[i]!=';'||i == num;i++,now++){
                Apassword[now] = allWord[i];
            }
            i++;
            Apassword[now] = '\0';
            if(i>=num){
                printf(1,"Login:AccountFile have error\n");
                break;
            }
                    
            now =0;
            for(;allWord[i]!='\n' && allWord[i]!='\0' ;i++,now++){
                AID[now] = allWord[i];
            }
            AID[now] = '\0';
            // printf(1,"%s\n",user);
            // printf(1,"%s\n",Auser);
            // printf(1,"%s\n",Apassword);
            //  printf(1,"%s\n",AID);
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
            printf(2,"Welcome %s\n",user);
        }
    }
    else
    {
        printf(2,"su: no such user\n");
    exit();
    }
            //printf(1,"%d\n",num);
    close(fd);
    close(writefd);
    exit();
}