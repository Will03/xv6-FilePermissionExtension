#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path, int commandNumber)
{
  char buf[512], *p, *fileName;
  int fd,flag;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

   if((flag = (fstat(fd, &st))) < 0){
    if(flag <= -2)
      printf(2, "ls: cannot stat %s :permission deny\n", path);  
    else
      printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      fileName = fmtname(buf);
      if(commandNumber == 0 && fileName[0] != '.')
        printf(1, "%s %d %d %d %d %d %d\n", fileName, st.type, st.ino, st.size, st.permission, st.ownerid,st.groupid);

      else if ( commandNumber == 0 &&  (!strcmp(fileName,".             ")||!strcmp(fileName,"..            ")))
        printf(1, "%s %d %d %d %d %d %d\n", fileName, st.type, st.ino, st.size, st.permission, st.ownerid,st.groupid);

      else if(commandNumber == 1)
        printf(1, "%s %d %d %d %d %d %d\n", fileName, st.type, st.ino, st.size, st.permission, st.ownerid,st.groupid);
      
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i, j, commandNumber = 0;
  const int commandAmount = 1;
  const char command[1][3] = { "-a" };

  if(argc < 2){
    ls(".", 0);
    exit();
  }
  for(i=1; i<argc; i++){
    int isNotCommand = 0;
    for(j=0; j<commandAmount; ++j){
      int index = 0, isCorrect = 1;
      while(argv[i][index] != '\0' && command[j][index] != '\0'){
        if(argv[i][index] != command[j][index]){
          isCorrect = 0;
          break;
        }
        ++index;
      }
      if(isCorrect)
        commandNumber = j+1;
      else
        isNotCommand = 1;
    }
    if(isNotCommand)
      ls(argv[i], commandNumber);
  }
  exit();
}
