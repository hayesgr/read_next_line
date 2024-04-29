#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
    int fd = open("get_next_line.h",O_RDONLY);
    if(fd==-1){
        printf("unable to openfile\n");
        exit(0);
    }
    char* t;
    while(1){
        //t = get_next_line(fd);
        t = get_next_line2(fd);
        if(t==NULL){break;}
        printf("%s",t);
        if(t){free(t);}
    }
    close(fd);
    return 0;
}
