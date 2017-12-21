#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#define MAXLEN 20
char *argv[] = { "sh", 0 };

int
CheckAccount(int fd ,int writefd, char *user , char *passwd)
{
    char allWord[128];
    char Auser[MAXLEN];
    char AID[10];
    char Apassword[MAXLEN];

    int num,now = 0;

    if(user[strlen(user)-1]  == '\n'){
  	    user[strlen(user)-1]  = '\0';	
    }
    if(passwd[strlen(passwd)-1]  == '\n'){
  	    passwd[strlen(passwd)-1]  = '\0';	
    }
    while((num = read(fd, allWord, sizeof(allWord))) > 0){
        now = 0;
        //printf(1,"%d\n",num);  
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
            // printf(1,"%s\n",Auser);
            // printf(1,"%s\n",Apassword);
            // printf(1,"%s\n",AID);
            
            if(!strcmp(user,Auser) && !strcmp(passwd,Apassword)){
                if(write(writefd,AID,sizeof(AID)) <= 0)
                printf(1,"error\n");
                //printf(1,"%d\n",num);
                close(fd);
                close(writefd);
                
                
                char * dirToCreate = "/home/";
      	        strcpy(dirToCreate + strlen(dirToCreate), user);
      	        //printf(1,"%s\n", dirToCreate);
      	        mkdir(dirToCreate);
      	        return 1;
            }
            //while(i <num && allWord[i++] != '\n');
        }
    }
    return 0;
}

int
main(void)
{
    int pid = 0,fd,writefd, wpid;
    char * username;
    char* password;
    mkdir("/home/");
    while(1)
    {
        printf(1,"Username: ");
		username = gets("username", MAXLEN);
		
        printf(1,"Password: ");
		password = gets("password", MAXLEN);
        dup(0);  // stdout
		dup(0);  // stderr
        //printf(1, "init:
        if((writefd = open("/nowuserid", O_WRONLY)) < 0){
            printf(1,"Login: can't open nowuserid\n");
            break;
        } 
        if((fd = open("/userpasswd", O_RDONLY)) < 0){
            printf(1,"Login: can't open Userpassword\n");
            break;
        }
        
        if(CheckAccount(fd,writefd,username,password)){
            printf(1,"Hello %s, have a nice's day\n", username);
            
            if((writefd = open("/nowuserid", O_RDONLY)) < 0){
            printf(1,"Login: can't open nowuserid\n");
            break; } 
            char a[20];
            if(read(writefd,a,sizeof(a))<=0)
                printf(1,"error\n");
            printf(1,"%s\n",a);
           
            pid = fork();
            if(pid < 0){
                printf(1, "login: fork failed\n");
                exit();
            }
            if(pid == 0){   
                //char * uname[] = {username};
                exec("sh", argv);
                printf(1, "login: exec sh failed\n");
                exit();
            }
        }
        else{
            printf(1,"you print error username or password\n");
            printf(1,"please input your account again\n");
        }

        close(fd);
        while((wpid=wait()) >= 0 && wpid != pid)
	    printf(1, "zombie!\n");
    }
    

    wait();
	exit();
	return 0;
}