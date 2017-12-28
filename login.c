#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "passwork.h"
#define MAXLEN 20
char *argv[] = { "sh", 0 };

int
CheckAccount(int fd ,int writefd, char *user , char *passwd)
{
    char allWord[128];
    char Auser[MAXLEN];
    char AID[10];
    char Apassword[MAXLEN];
    char cipher[MAXLEN];
    int num;

    if(user[strlen(user)-1]  == '\n'){
  	    user[strlen(user)-1]  = '\0';	
    }
    if(passwd[strlen(passwd)-1]  == '\n'){
  	    passwd[strlen(passwd)-1]  = '\0';	
    }

    while((num = read(fd, allWord, sizeof(allWord))) > 0){
        //printf(1,"%d\n",num);  
        for(int i =0;i<num;i++)
        {

            i = readpasswdfile(allWord,Auser,Apassword,AID,num,i);
            if(i == -1)break;
            
            
            
            encodepasswd(cipher,passwd);

            if(!strcmp(user,Auser) && !strcmp(cipher,Apassword)){


                if(write(writefd,AID,sizeof(AID)) <= 0)
                    printf(1,"error\n");
                int now = 0,id = 0,mod = 0;
            

                for(int i =0 ;AID[i]!=';'&& AID[i]!='\0';i++,now++){
                    id *= 10;
                    
                    id += AID[i] - 48;
                }
                printf(2,"%d %d\n",setuid(id,mod),setgid(id,mod));
                printf(2,"%d\n",getuid());
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
    char namebuf[MAXLEN];
    char passwdbuf[MAXLEN];
    char* password;
    mkdir("/home/");
    chmod("home",777);
    while(1)
    {
        printf(1,"Username: ");
		username = gets(namebuf, MAXLEN);
		
        printf(1,"Password: ");
		password = gets(passwdbuf, MAXLEN);


        dup(0);  // stdout
	    dup(0);  // stderr
        //printf(1, "init:
        if((writefd = open("/.nowuserid", O_WRONLY)) < 0){
            printf(1,"Login: can't open nowuserid\n");
            break;
        } 
        if((fd = open("/.userpasswd", O_RDONLY)) < 0){
            printf(1,"Login: can't open Userpassword\n");
            break;
        }
        
        if(CheckAccount(fd,writefd,username,password)){
	        close(fd);
            close(writefd);
	    
            printf(2,"Hello %s, have a nice's day\n", username);            
            if((writefd = open("/.nowuserid", O_RDONLY)) < 0){
            printf(1,"Login: can't open nowuserid\n");
            break; } 
            char a[20];
            if(read(writefd,a,sizeof(a))<=0)
                printf(1,"error\n");
            printf(2,"%s\n",a);
           
            pid = fork();
            if(pid < 0){
                printf(1, "login: fork failed\n");
                exit();
            }
            if(pid == 0){   
                char * uname[] = {username,0};
		        char * dirToCreate = "/home/";
      	    	strcpy(dirToCreate + strlen(dirToCreate), username);
                mkdir(dirToCreate);
                exec("sh", uname);
                printf(1, "login: exec sh failed\n");
                exit();
            }
        }
        else{
            close(fd);
            close(writefd);
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
