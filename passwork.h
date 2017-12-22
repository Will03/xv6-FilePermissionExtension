#include "types.h"
#include "user.h"
#include "syscall.h"
#include "fcntl.h"

int
readpasswdfile(char* allWord,char* Auser,char* Apassword ,char* AID,int num,int i)
{
    int now = 0;
    for(;allWord[i]!=';'||i == num;i++,now++){
        Auser[now] = allWord[i];
    }
    i++;
    Auser[now] = '\0';
    if(i>=num){
        printf(1,"Login:AccountFile have error\n");
        return -1;
    }
    
    now =0;
    for(;allWord[i]!=';'||i == num;i++,now++){
        Apassword[now] = allWord[i];
    }
    i++;
    Apassword[now] = '\0';
    if(i>=num){
        printf(1,"Login:AccountFile have error\n");
        return -1;
    }
            
    now =0;
    for(;allWord[i]!='\n' && allWord[i]!='\0' ;i++,now++){
        AID[now] = allWord[i];
    }
    AID[now] = '\0';
    // printf(1,"%s\n",Auser);
    // printf(1,"%s\n",Apassword);
    // printf(1,"%s\n",AID);
    return i;
}

