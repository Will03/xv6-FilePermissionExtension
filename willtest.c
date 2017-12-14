#include "willtest.h"
#include "user.h"
int willopen()
{
    int fp = 0;
    char id[id_length];
    fp = open("/nowuserid",O_RDONLY);
    read(fp,id,sizeof(char)*id_length);

    return atoi(id);
}