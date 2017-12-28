#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "passwork.h"
int main(void)
{
    printf(2,"%d\n",setuid(20,1));

    wait();
	exit();
}