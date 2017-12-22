#include "types.h"
#include "user.h"
#include "syscall.h"
#include "fcntl.h"
#define MAXLEN 20
int
seachlastuserid(char* allWord,int num,char* newid)
{
    int now = 0;
    char AID[10];
    for(int i =0;i<num;i++)
    {
        for(;allWord[i]!=';'||i == num;i++,now++);
        i++;
        if(i>=num){
            printf(1,"Login:AccountFile have error\n");
            return -1;
        }
        
        now =0;
        for(;allWord[i]!=';'||i == num;i++,now++);
        i++;
        if(i>=num){
            printf(1,"Login:AccountFile have error\n");
            return -1;
        }    
        now =0;
        for(;allWord[i]!=';'||i == num;i++,now++){
            AID[now] = allWord[i];
        }
        for(;allWord[i]!='\n' && allWord[i]!='\0';i++,now++);
        AID[now] = '\0';
        //printf(1,"%s\n",AID);
        
    }
    int id = atoi(AID);
    int number = 0;
    char tem;
    id+=1;
    for(int n = 0;;number++)
    {
        n = id%10;
        id/=10;
        AID[number] = n+48;
        if(id==0)break;
    }
    for(int i =0,j=number;;i++,j--)
    {
        if(i >= j)break;
        tem = AID[i];
        AID[i] = AID[j];
        AID[j] = tem;
    }
    AID[number+1] = '\0';
    strcpy(newid,AID);
    return 1;
}

int main(int argc, char *argv[])
{
    int fd,num,flag = 0;
    char allWord[128],buf[64],newid[8],idbuf[17];
    if(argc != 3)
    {
        printf(2, "userpasswd: you need to input username and password\n");
        exit();
    }
    if((fd = open("/userpasswd", O_RDONLY)) < 0){
        printf(1,"useradd: can't open Userpassword\n");
        exit();
    }
    while((num = read(fd, allWord, sizeof(allWord))) > 0){
        if(num>0){
            flag = seachlastuserid(allWord,num,newid);
        }
        else{
            printf(2,"useradd: error to read userpasswd\n");
            close(fd);
            exit();
        }
    }
    if(flag >0){
        //printf(2,"id:%s\n",newid);
        for(num = 0;newid[num] == '\0';num++);
        num++;
        strcpy(idbuf,newid);
        strcpy(idbuf+strlen(idbuf),";");
        strcpy(idbuf+strlen(idbuf),newid);
        strcpy(idbuf+strlen(idbuf),"\n");
        // printf(2,"%d\n",num);
        // printf(2,"%s\n",idbuf);
        close(fd);
        if((fd = open("/userpasswd", O_RDWR)) < 0){
            printf(1,"useradd: can't open Userpassword\n");
            exit();
        }
        if(read(fd, allWord, sizeof(allWord)) == 0){
            printf(2,"useradd: error to add new user\n");
            close(fd);
            exit();
        }
        strcpy(buf,argv[1]);
        strcpy(buf+strlen(buf),";");
        strcpy(buf+strlen(buf),argv[2]);
        strcpy(buf+strlen(buf),";");
        strcpy(buf+strlen(buf),idbuf);
        printf(2,"%s",buf);
        if( !write(fd, buf,strlen(buf))){
            printf(2,"useradd: error to add new user\n");
        }
        close(fd);
    }
    exit();
}