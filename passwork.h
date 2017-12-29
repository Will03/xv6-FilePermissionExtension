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
    //,char* passwdkey
    //Key string
    for(;allWord[i]!=';'||i == num;i++,now++);
    i++;
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

//set a radom string
void pseudoRandom(char key, char encodeKey[], int len) {
  int i;
  unsigned char ran;
  unsigned char bnew;
  encodeKey[0] = key;
  for (i=1; i<len; i++) {
    ran = (unsigned char) encodeKey[i-1];
    bnew = (ran * 7) % 255;
    encodeKey[i] = (char) bnew;
  }
encodeKey[i] = '\0';
}
 
// start encrypt
void encrypt(char plan[], char cipher[], char encodeKey[], int len) {
  int i;
  for (i=0; i<len; i++) {
    cipher[i] = plan[i] ^ encodeKey[i];
    if(cipher[i]<0)cipher[i]*=-1;
    cipher[i] = (cipher[i]%25)+65;
  }
  cipher[i] = '\0';
}

void encodepasswd(char* cipher, char* passwd)
{
    char key = 0x6D;
    char encodeKey[20];
    pseudoRandom(key, encodeKey, strlen(passwd));
    encrypt(passwd, cipher, encodeKey,strlen(passwd));
}